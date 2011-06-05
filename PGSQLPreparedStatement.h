//
//  PGSQLPreparedStatement.h
//  PGSQLKit
//
//  Created by Andy Satori on 1/30/09.
//  Copyright 2009 Druware Software Designs. All rights reserved.
//

//#import <Cocoa/Cocoa.h>

@class PGSQLRecordset;

@interface PGSQLPreparedStatement : NSObject {
	NSString *statementName;
	
	NSString *sqlCommand;
	NSArray *parameters;
}

-(BOOL)prepare;

-(BOOL)exec;
-(PGSQLRecordset *)open;
-(void)execAsync;
-(void)openAsync;

-(NSString *)statementName;
-(void)setStatementName:(NSString *)value;

-(void *)parameterByIndex:(int)index;
-(void)setParameter:(void *)value forIndex:(int)index ofType:(int)SQL_TYPE;

@end
