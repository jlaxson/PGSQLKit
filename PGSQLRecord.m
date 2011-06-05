//
//  PGSQLRecord.m
//  PGSQLKit
//
//  Created by Andy Satori on 6/7/07.
//  Copyright 2007 Druware Software Designs. All rights reserved.
//

/* License *********************************************************************
 
 Copyright (c) 2005-2009, Druware Software Designs 
 All rights reserved. 
 
 Redistribution and use in source or binary forms, with or without modification,
 are permitted provided that the following conditions are met: 
 
 1. Redistributions in source or binary form must reproduce the above copyright 
 notice, this list of conditions and the following disclaimer in the 
 documentation and/or other materials provided with the distribution. 
 2. Neither the name of the Druware Software Designs nor the names of its 
 contributors may be used to endorse or promote products derived from this 
 software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE 
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 
 *******************************************************************************/

#import "PGSQLRecord.h"
#include "libpq-fe.h"

@implementation PGSQLRecord


-(id)initWithResult:(void *)result atRow:(long)atRow columns:(NSArray *)columncache
{
	[super init];

	pgResult = result;
	columns = columncache;
	rowNumber = atRow;
	
	// this will default to NSUTF8StringEncoding with PG9
	defaultEncoding = NSMacOSRomanStringEncoding;
	
	return self;
}

-(PGSQLField *)fieldByName:(NSString *)fieldName
{
	// find the field index from the columns.
	int x = 0;
	PGSQLColumn *column = nil;
	
	for (x = 0; x < [columns count]; x++)
	{
		if ([[[columns objectAtIndex:x] name] caseInsensitiveCompare:fieldName] == NSOrderedSame)
		{
			column = [columns objectAtIndex:x];
			break;
		}
	}
	
	PGSQLField *result = [[PGSQLField alloc] initWithResult:pgResult forColumn:column
														   atRow:rowNumber];
	[result setDefaultEncoding:defaultEncoding];
	
	return [result autorelease];
}

-(PGSQLField *)fieldByIndex:(long)fieldIndex
{
	// find the field index from the columns.
	PGSQLField *result = [[PGSQLField alloc] initWithResult:pgResult forColumn:[columns objectAtIndex:fieldIndex]
													  atRow:rowNumber];
	[result setDefaultEncoding:defaultEncoding];

	return [result autorelease];
}

-(long)rowNumber
{
	return rowNumber;
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
