//
//  PGSQLField.m
//  PGSQLKit
//
//  Created by Andy Satori on 6/7/07.
//  Copyright 2007 Druware Software Designs. All rights reserved.
//

#import "PGSQLField.h"
#include "libpq-fe.h"

@implementation PGSQLField

-(id)initWithResult:(void *)result forColumn:(PGSQLColumn *)forColumn
			  atRow:(int)atRow
{
	self = [super init];
	
	if (self)
	{
		data = nil;
		
		// this will default to NSUTF8StringEncoding with PG9
		defaultEncoding = NSMacOSRomanStringEncoding;

		if (PQgetisnull(result, atRow, [forColumn index]) != 1)
		{		
			char* szBuf = nil;
			
			column = [forColumn retain];
			
			int format = PQfformat(result, [column index]);
			
			int iLen = PQgetlength(result, atRow, [column index]);			// Binary
			if (format == 0)
			{
				iLen = PQgetlength(result, atRow, [column index]) + 1;		// Text
			}
			
			// this may have to be adjust if the column type is not 0 (eg, it's binary)
			szBuf = PQgetvalue(result, atRow, [column index]);
			if (iLen > 0)
				data = [[NSData alloc] initWithBytes:szBuf length:iLen];
		}
	}

	return self;
}

- (void)dealloc
{
	[data release];
	[column release];
	[super dealloc];
}

-(NSString *)asString
{	
	NSString* result = @"";
	if (data != nil)
	{
		int dataLength = [data length];
		if (dataLength > 0)
		{
			// check for null terminator
			char* ptr = (char*)[data bytes];
			char lastChar = ptr[dataLength - 1];
			if (lastChar == '\0')
				dataLength--;
			if (dataLength > 0)
				result = [[[NSString alloc] initWithBytes:[data bytes] length:dataLength encoding:defaultEncoding] autorelease];
		}
	}
	return result; 
}

-(NSString *)asString:(NSStringEncoding)encoding
{	
		NSString* result = @"";
		if (data != nil)
		{
			int dataLength = [data length];
			if (dataLength > 0)
			{
				// check for null terminator
				char* ptr = (char*)[data bytes];
				char lastChar = ptr[dataLength - 1];
				if (lastChar == '\0')
					dataLength--;
				if (dataLength > 0)
					result = [[[NSString alloc] initWithBytes:[data bytes] length:dataLength encoding:encoding] autorelease];
			}
		}
		return result; 
}

-(NSNumber *)asNumber
{
	if (data != nil) {
		if ([data length] <= 0)
		{
			return nil;
		}
		NSString *temp = [[[NSString alloc] initWithBytes:[data bytes] length:[data length] encoding:NSUTF8StringEncoding] autorelease];
		NSNumber *value = [[[NSNumber alloc] initWithFloat:[temp floatValue]] autorelease];
		return value;
	}
	return nil;
}

-(long)asLong
{
	if (data != nil) {
		if ([data length] <= 0)
		{
			return 0;
		}
		
		NSString *value = [[[NSString alloc] initWithBytes:[data bytes] length:[data length] encoding:NSUTF8StringEncoding] autorelease];
		
		return (long)[[NSNumber numberWithFloat:[value floatValue]] longValue];
	}
	return 0; 
}

-(NSDate *)asDate
{
    static NSDateFormatter *formatter = nil;
    
    if (formatter == nil) {
        formatter = [[NSDateFormatter alloc] init];
        [formatter setDateFormat:@"yyyy'-'MM'-'dd HH':'mm':'ssZZ"];
    }
    
    if (data != nil) {
		if ([data length] <= 0)
		{
			return nil;
		}
        
        NSString *value = [NSString stringWithCString:(char *)[data bytes]
											 encoding:NSUTF8StringEncoding];
        value = [value stringByAppendingString:@"00"];
        NSDate *d = [formatter dateFromString:value];
        return d;
    }
    
    return nil;
    
	if (data != nil) {
		if ([data length] <= 0)
		{
			return nil;
		}
		
		NSString *value = [NSString stringWithCString:(char *)[data bytes]
											 encoding:NSUTF8StringEncoding];
		if ([value rangeOfString:@"."].location != NSNotFound)
		{
			value = [NSString stringWithFormat:@"%@ +0000", [value substringToIndex:[value rangeOfString:@"."].location]];
		} else {
			
			value = [NSString stringWithFormat:@"%@ +0000", value];
		}
		NSDate *newDate = [[[NSDate alloc] initWithString:value] autorelease];
		
		return newDate;
	}
	return nil; 	
}

-(NSData *)asData
{
	if (data != nil) {
		if ([data length] <= 0)
		{
			return nil;
		}
        
        size_t len;
        const unsigned char *unescaped = PQunescapeBytea([data bytes], &len);
		
		return [[[NSData alloc] initWithBytes:unescaped length:len] autorelease];
	}
	return nil; 	
}

-(BOOL)asBoolean
{
	BOOL result = NO;
	if (data != nil)
	{
		char charResult = *(char*)[data bytes];
		result = (charResult == 't');
	}
	return result;
}

-(BOOL)isNull
{
	return (data == nil);
}

-(NSStringEncoding)defaultEncoding
{
	return defaultEncoding;
}

-(void)setDefaultEncoding:(NSStringEncoding)value
{
    if (defaultEncoding != value) {
        defaultEncoding = value;
    }	
	
}

@end;
