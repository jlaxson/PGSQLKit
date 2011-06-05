//
//  PGSQLRecord.h
//  PGSQLKit
//
//  Created by Andy Satori on 6/7/07.
//  Copyright 2007 Druware Software Designs. All rights reserved.
//

/*!
    @header PGSQLRecord
    @abstract   An individual row in a resultset.
    @discussion The PGSQLRecord provides the PGSQLKit interface to the row of 
				data in a recordset.
 
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

#import "PGSQLField.h";

/*!
    @class
    @abstract    PGSQLRecord is the PGSQLKit implementation of an individual 
				 result row in a a recordset.  This class is never created 
				 outside the context of a resultset.
    @discussion  Provides a relatively simple accessor to the child fields, and
				 is rarely directly referenced in any but the most vague way.
*/
@interface PGSQLRecord : NSObject {	
	void *pgResult;
	long  rowNumber;
	NSArray *columns;
	NSStringEncoding defaultEncoding;
}

-(id)initWithResult:(void *)result atRow:(long)atRow columns:(NSArray *)columncache;

-(PGSQLField *)fieldByIndex:(long)fieldIndex;
-(PGSQLField *)fieldByName:(NSString *)name;

-(long)rowNumber;

/*!
	@function
	@abstract   Get the record's defaultEncoding for all string operations 
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
				record
	@discussion The default setting is NSMacOSRoman.  While this default is 
				used to maintain existing functionality, this will be changed 
				NSUTF8StringEncoding when PostgreSQL9 is released.
	@param      value the defaultEncoding as an NSSTringEncoding ( 
				http://developer.apple.com/mac/library/documentation/Cocoa/Reference/Foundation/Classes/NSString_Class/Reference/NSString.html#//apple_ref/doc/c_ref/NSStringEncoding )
	@result     void
 */
-(void)setDefaultEncoding:(NSStringEncoding)value;


@end
