//
//  PGSQLRecordset.m
//  PGSQLKit
//
//  Created by Andy Satori on 5/29/07.
//  Copyright 2007 Druware Software Designs. All rights reserved.
//

#import "PGSQLRecordset.h"
#import "libpq-fe.h"

@implementation PGSQLRecordset

-(id)initWithResult:(void *)result
{
    self = [super init];
	if (self != nil)
	{
		isOpen = YES;
		isEOF = YES;
		
		// this will default to NSUTF8StringEncoding with PG9
		// defaultEncoding = NSMacOSRomanStringEncoding;
		
		columns = [[[[NSMutableArray alloc] init] retain] autorelease];
		
		pgResult = result;
		
		rowCount = -1;
		rowCount = PQntuples(pgResult);
		
		// cache the colum list for faster data access via lookups by name
		// Loop through and get the fields into Field Item Classes
		PGSQLColumn *column;
		
		int iCols = 0;
		iCols = PQnfields(pgResult);
		
		int i;
		for ( i = 0; i < iCols; i++)
		{
			column = [[[PGSQLColumn alloc] initWithResult:pgResult 
												   atIndex:i] autorelease];
			[columns addObject:column];
		}
		
		if (rowCount == 0)
		{
			isEOF = YES;
			return self;
		}
		
		isEOF = NO;
		
		// move to the first record (and check EOF / BOF state)
		[self moveFirst];
	}
    return self;
}

-(PGSQLField *)fieldByName:(NSString *)fieldName
{
	return [currentRecord fieldByName:fieldName];
}

-(PGSQLField *)fieldByIndex:(long)fieldIndex
{
	return [currentRecord fieldByIndex:fieldIndex];
}

- (NSArray *)columns
{
	return columns;
}

- (long)recordCount
{
	return rowCount;
}

- (void)setCurrentRecordWithRowIndex:(long)rowIndex
{
	[currentRecord release];
	currentRecord = [[PGSQLRecord alloc] initWithResult:pgResult
														atRow:rowIndex
													  columns:columns];
	[currentRecord setDefaultEncoding:defaultEncoding];
}

- (PGSQLRecord *)moveNext
{
	if (rowCount == 0) {
		return nil;
	}
	
	long currentRowIndex = -1;
	if (currentRecord != nil) 
	{
		currentRowIndex = [currentRecord rowNumber];
	}
	currentRowIndex++;
	
	if (currentRowIndex >= rowCount) {
		isEOF = true;
		[currentRecord release];
		currentRecord = nil;
		return nil;
	}
	
	[self setCurrentRecordWithRowIndex:currentRowIndex];
	return [[currentRecord retain] autorelease];
}

- (PGSQLRecord *)moveFirst
{
	if (rowCount == 0) {
		return nil;
	}
	long currentRowIndex = 0;
	isEOF = false;
	
	[self setCurrentRecordWithRowIndex:currentRowIndex];
	return [[currentRecord retain] autorelease];
}

- (PGSQLRecord *)movePrevious
{
	if (rowCount == 0) {
		return nil;
	}
	long currentRowIndex = -1;
	if (currentRecord != nil) 
	{
		currentRowIndex = [currentRecord rowNumber];
	}
	currentRowIndex--;
	
	if (currentRowIndex < 0) {
		isEOF = true;
		currentRecord = nil;
		return nil;
	}
	
	[self setCurrentRecordWithRowIndex:currentRowIndex];
	return [[currentRecord retain] autorelease];
}

- (PGSQLRecord *)moveLast
{
	if (rowCount == 0) {
		return nil;
	}
	long currentRowIndex = rowCount;
	isEOF = false;

	[self setCurrentRecordWithRowIndex:currentRowIndex];
	return [[currentRecord retain] autorelease];
}

-(void)close
{
	if (isOpen) {
		[columns release];
		columns = nil;
		PQclear(pgResult);
		pgResult = nil;
	}
	[currentRecord release];
	currentRecord = nil;
	isOpen = NO;
}

-(void)dealloc
{
	[self close];
	[super dealloc];
}

-(BOOL)isEOF
{
	return isEOF;
}

-(NSDictionary *)dictionaryFromRecord
{
	NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
	long i;
	for (i = 0; i < [columns count]; i++)
	{
		PGSQLColumn *column = [columns objectAtIndex:i];
		
		// for each column, add the value for the key.
		// select oid, typname from pg_type
		
		switch ([column type])
		{
/*
			case SQL_UNKNOWN_TYPE:
				[dict setValue:[[self fieldByName:[column name]] asData] forKey:[[column name] lowercaseString]];
				break;				
			case SQL_CHAR:
			case SQL_VARCHAR:
				[dict setValue:[[self fieldByName:[column name]] asString] forKey:[[column name] lowercaseString]];
				break;
			case SQL_NUMERIC:
			case SQL_DECIMAL:
			case SQL_INTEGER:
			case SQL_SMALLINT:
			case SQL_FLOAT:
			case SQL_REAL:
			case SQL_DOUBLE:
				[dict setValue:[[self fieldByName:[column name]] asNumber] forKey:[[column name] lowercaseString]];
				break;				
			case SQL_DATETIME:
				[dict setValue:[[self fieldByName:[column name]] asDate] forKey:[[column name] lowercaseString]];
				NSLog(@"Date Being Set: %@ for: %@", [[self fieldByName:[column name]] asDate], [[column name] lowercaseString]);
				break;
			case 11: // Undefined, MSSQL SHORTDATETIME
				[dict setValue:[[self fieldByName:[column name]] asDate] forKey:[[column name] lowercaseString]];
				NSLog(@"Date Being Set: %@ for: %@", [[self fieldByName:[column name]] asDate], [[column name] lowercaseString]);
				break;
*/
			case 16: // BOOL
				if ([[self fieldByName:[column name]] asBoolean])
				{
					[dict setValue:@"true" forKey:[column name]];
				} else {
					[dict setValue:@"false" forKey:[column name]];
				}
				break;
			default:
				[dict setValue:[[self fieldByName:[column name]] asString:defaultEncoding] forKey:[column name]];
				break;
		}
	}
	NSDictionary *result = [[[NSDictionary alloc] initWithDictionary:dict] autorelease];
	[dict release];
	return result;
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


@end
