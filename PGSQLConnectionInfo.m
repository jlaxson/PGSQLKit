//
//  PGSQLConnectionInfo.m
//  PGSQLKit
//
//  Created by Andy Satori on 4/21/09.
//  Copyright 2009 Druware Software Designs. All rights reserved.
//

#import "PGSQLConnectionInfo.h"

@implementation PGSQLConnectionInfo

-(id)initWithConnection:(PGSQLConnection *)connection
{
	[super init];
	
	pgConnection = connection;
	[pgConnection retain];
	
	NSMutableString *cmd = [[NSMutableString alloc] init];
	[cmd appendString:@"select current_database() as db, current_user as user, version() as version, current_schema() as schema"]; 
	PGSQLRecordset *rs = [pgConnection open:cmd];
	if (![rs isEOF])
	{
		//userName = [[rs fieldByIndex:1] asString];
		versionString = [[rs fieldByIndex:2] asString];
		//schemaName = [[rs fieldByIndex:3] asString];
	}
	[rs close];
	[cmd  release];
	
	return self;
}

-(void)dealloc
{
	[pgConnection release];
	
	[super dealloc];
}

#pragma mark -
#pragma mark Simple Accessors

- (NSString *)versionString
{
	return versionString;
}

@end
