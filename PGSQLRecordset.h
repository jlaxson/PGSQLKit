//
//  PGSQLRecordset.h
//  PGSQLKit
//
//  Created by Andy Satori on 5/29/07.
//  Copyright 2007 Druware Software Designs. All rights reserved.
//

/*!
    @header PGSQLRecordset
    @abstract   A represention of a result from a sql command.  
	@discussion Where the connection is the root of all data access, the 
				recordset is the root of all data read operations in the
				PGSQLKit.  Allowing the user to navigate through the result
				using a collection of PGSQLRecords, which then contain the 
				PGSQLFields that contain the data elements.  

				Of particular note is the dictionaryFromRecord method which 
				provides a convenient 'record to NSDictionary' translation that
				often eases consumption of the data in the realm of Cocoa 
				Bindings.
 
				License 

				Copyright (c) 2005-2010, Druware Software Designs
				All rights reserved.

				Redistribution and use in binary forms, with or without 
				modification, are permitted provided that the following 
				conditions are met:

				1. Redistributions in binary form must reproduce the above 
				   copyright notice, this list of conditions and the following 
				   disclaimer in the documentation and/or other materials 
				   provided with the distribution. 
				2. Neither the name of the Druware Software Designs nor the 
				   names of its contributors may be used to endorse or promote 
				   products derived from this software without specific prior 
				   written permission.

				THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
				CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
				INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
				MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
				DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
				CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
				SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
				LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
				USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
				AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
				LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
				IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
				THE POSSIBILITY OF SUCH DAMAGE.
 
*/

#import "PGSQLColumn.h"
#import "PGSQLRecord.h"
#import "PGSQLField.h"
	
/*!
    @class
    @abstract    The PGSQLRecordset is the result of any command that returns a
				 result.  It provides the column list, as well as methods to 
				 read the data from the result.
    @discussion  Where the connection is the root of all data access, the 
				 recordset is the root of all data read operations in the
				 PGSQLKit.  Allowing the user to navigate through the result
				 using a collection of PGSQLRecords, which then contain the 
				 PGSQLFields that contain the data elements.  
 
				 Of particular note is the dictionaryFromRecord method which 
				 provides a convenient 'record to NSDictionary' translation that
				 often eases consumption of the data in the realm of Cocoa 
				 Bindings.
*/
@interface PGSQLRecordset : NSObject {
	void *pgResult;
	
	BOOL isEOF;
	BOOL isOpen;
	
	long rowCount;
	
	NSMutableArray *columns;
	
	PGSQLRecord *currentRecord;
	
	NSStringEncoding defaultEncoding;
}

-(id)initWithResult:(void *)result;
-(PGSQLField *)fieldByIndex:(long)fieldIndex;
-(PGSQLField *)fieldByName:(NSString *)fieldName;
-(void)close;

-(NSArray *)columns;

- (long)recordCount;

-(PGSQLRecord *)moveFirst;
-(PGSQLRecord *)movePrevious;
-(PGSQLRecord *)moveNext;	
-(PGSQLRecord *)moveLast;

-(BOOL)isEOF;

-(NSDictionary *)dictionaryFromRecord;

/*!
	@function
	@abstract   Get the recordset's defaultEncoding for all string operations 
				results.
	@discussion The default setting is NSMacOSRoman.  While this default is 
				used to maintain existing functionality, this will be changed 
				NSUTF8StringEncoding when PostgreSQL9 is released.
	@result     returns the defaultEncoding as an NSSTringEncoding ( 
				http://developer.apple.com/mac/library/documentation/Cocoa/Reference/Foundation/Classes/NSString_Class/Reference/NSString.html#//apple_ref/doc/c_ref/NSStringEncoding )
 */
-(NSStringEncoding)defaultEncoding;
/*!
	@function
	@abstract   Set the defaultEncoding for all string operations on the current
				recordset
	@discussion The default setting is NSMacOSRoman.  While this default is 
				used to maintain existing functionality, this will be changed 
				NSUTF8StringEncoding when PostgreSQL9 is released.
	@param      value the defaultEncoding as an NSSTringEncoding ( 
				http://developer.apple.com/mac/library/documentation/Cocoa/Reference/Foundation/Classes/NSString_Class/Reference/NSString.html#//apple_ref/doc/c_ref/NSStringEncoding )
	@result     void
 */
-(void)setDefaultEncoding:(NSStringEncoding)value;

@end

