//
//  PGSQLField.h
//  PGSQLKit
//
//  Created by Andy Satori on 6/7/07.
//  Copyright 2007-2010 Druware Software Designs. All rights reserved.
//

/*!
    @header		PGSQLField
	@abstract   A simple Field class that is the end point of most data access 
				in PGSQLKit.  Contextually, the PGSQLField encapsulates an 
				NSData * that represents the raw bytes of data returned from the
				database.  
 
	@discussion The PGSQLField class provides the data from the individual field
				in consumable fashion.  This includes methods for fetching that 
				raw data, or data formatted to the desired format. 
 
				License 

				Copyright (c) 2005-2010, Druware Software Designs
				All rights reserved.

				Redistribution and use in binary forms, with or without modification, are 
				permitted provided that the following conditions are met:

				1. Redistributions in binary form must reproduce the above copyright notice, 
				this list of conditions and the following disclaimer in the documentation 
				and/or other materials provided with the distribution. 
				2. Neither the name of the Druware Software Designs nor the names of its 
				contributors may be used to endorse or promote products derived from this 
				software without specific prior written permission.

				THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
				AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
				IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
				ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
				LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
				CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
				SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
				INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
				CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
				ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
				THE POSSIBILITY OF SUCH DAMAGE.

*/

#import "PGSQLColumn.h"


/*!
	@class
	@abstract	The PGSQLField is the encapsulated representation of the 
				individual data field in the resultset.  It is never directly
				created, and should only be referenced as a part of the 
				PGSQLRecord.
 
	@discussion	
 */
@interface PGSQLField : NSObject {
	NSData *data;
	
	PGSQLColumn *column;
	
	NSStringEncoding defaultEncoding;
}

-(id)initWithResult:(void *)result forColumn:(PGSQLColumn *)forColumn
			  atRow:(int)atRow;
/*!
	@method     
	@abstract   Returns a string representation of the raw data.  By default, 
				strings using this method default to an NSMacRomanStringEncoding.
	@discussion Returns a string representation of the raw data.  
*/
-(NSString *)asString;
/*!
    @method     
    @abstract   Returns a string representation of the raw data.  This variant
				takes an NSStringEncoding parameter to allow the user to obtain
				the data in a more appropriate encoding.
	@discussion Returns a string representation of the raw data.  This variant
				takes an NSStringEncoding parameter to allow the user to obtain
				the data in a more appropriate encoding.  The possible encodings
				are the same as a standard NSString.  
 
				http://developer.apple.com/mac/library/documentation/Cocoa/Reference/Foundation/Classes/NSString_Class/Reference/NSString.html#//apple_ref/doc/constant_group/String_Encodings
*/
-(NSString *)asString:(NSStringEncoding)encoding;
-(NSNumber *)asNumber;
-(long)asLong;
-(NSDate *)asDate;
-(NSData *)asData;
-(BOOL)asBoolean;

-(BOOL)isNull;

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
