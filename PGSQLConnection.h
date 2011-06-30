//
//  PGSQLConnection.h
//  PGSQLKit
//
//  Created by Andy Satori on 5/8/07.
//  Copyright 2007-2010 Druware Software Designs. All rights reserved.
//

/*!
 @header PGSQLConnection
 @abstract		A Connection class that is the root of all data access in 
				PGSQLKit.  Contextually, the PGSQLConnection encapsulates a 
				PQconnectdb() call and the results of that call.
 
 @discussion	The PGSQLConnection class provides the gateway to all of the 
				functionality in the library.  The only class that is not 
				reached through the Connection class is the Login class, which 
				is a utility class intended to provide an easy and reusable 
				tool for obtaining a Connection class without reinventing the
				login panel in every application.
 
				The core functionality of this class wraps around the libpq 
				interface.
 
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

// #import <Cocoa/Cocoa.h>
#import "PGSQLRecordset.h"

/*!
 @class
 @abstract		PGSQLConnection is the core class in the Kit.  Using the 
				PGSQLConnection to create and use a database connection to 
				execute queries and return results from the database, everything
				else in the kit stems from this core class.
 @discussion	The usual use of this class is to create a connection that is 
				used for the duration of the connection.  A single connection 
				can support multiple queries, however, because of local storage
				of the results, it is possible that memory could become a 
				concern if mulitple result sets are open as the same time.
 */
@interface PGSQLConnection : NSObject {	
	BOOL isConnected;
	
	NSString *connectionString;
	
	NSString *errorDescription;
	NSMutableString	*sqlLog;
	NSStringEncoding defaultEncoding;
	
	/* platform specific definitions */
	
	
	BOOL logInfo;
	BOOL logSQL;
	
	void			*pgconn;
	
	NSString		*host;
	NSString		*port;
	NSString		*options;
	NSString		*tty;		// ignored now
	NSString		*dbName;
	NSString		*userName;
	NSString		*password;
	NSString		*sslMode;	// allow, prefer, require
	NSString		*service;	// service name
	NSString		*krbsrvName;
		
	NSString		*commandStatus;
}

/*!
    @method
    @abstract   If a connection has been established, it will be maintained as
				the defaultConnection.  
    @discussion The defaultConnection is treated as a singleton and will ALWAYS
				be the first connection established in an instance of the 
				PGSQLKit framework.  It will not span processes.
 
				The defaultConnection will return an id as a PGSQLConnection * 
				to the the first connection made in the current session.
*/
+(id)defaultConnection;

#pragma mark -
#pragma mark Contructor / Destructor Functions

/*!
    @function     
    @abstract   Initialize the class.  Though this is a standard to every Cocoa 
				class, the PGSQLConnection also uses this method to set a sane 
				base environment so as not presume compiler and runtime defaults.
    @discussion During init, the PGSQLConnection clears and defaults all of the 
				properties in order to prevent unexpected values in any of the 
				parameters.  Though this is not normally a concern, there are a 
				couple of defaults to be aware of:
 
				host - defaults to "localhost"
				port - defaults to 5432
				dbName - defaults to "template1"
				
				If the defaultConnection is not already assigned from a prior 
				connection, then the defaultConnection is also set to be the 
				current connection upon init.
*/
-(id)init;
-(void)dealloc;

#pragma mark -
#pragma mark Connection Management Functions

-(BOOL)close;
-(BOOL)connect;
-(void)connectAsync;
-(BOOL)reset;
-(NSMutableString *)makeConnectionString;

#pragma mark -
#pragma mark Sql Execution Functions

-(BOOL)execCommand:(NSString *)sql;
- (BOOL)execCommand:(NSString *)sql numberOfArguments:(int)nParams withParameters:(id)params,...;
-(void)execCommandAsync:(NSString *)sql;
- (PGSQLRecordset *)open:(NSString *)sql numberOfArguments:(int)nParams withParameters:(id)param, ...;
-(PGSQLRecordset *)open:(NSString *)sql;
-(void)openAsync:(NSString *)sql;

#pragma mark -
#pragma mark Utility Functions

-(NSData *)sqlDecodeData:(NSData *)toDecode;
-(NSString *)sqlEncodeData:(NSData *)toEncode;
-(NSString *)sqlEncodeString:(NSString *)toEncode;

#pragma mark -
#pragma mark Simple Accessors

-(BOOL)isConnected;

-(NSString *)connectionString;
-(void)setConnectionString:(NSString *)value;

-(NSString *)userName;
-(void)setUserName:(NSString *)value;

-(NSString *)password;
-(void)setPassword:(NSString *)value;

-(NSString *)server;
-(void)setServer:(NSString *)value;

-(NSString *)port;
-(void)setPort:(NSString *)value;

-(NSString *)databaseName;
-(void)setDatabaseName:(NSString *)value;

-(NSString *)lastError;

-(NSMutableString *)sqlLog;
-(void)appendSQLLog:(NSString *)value;

/*!
    @function
    @abstract   Get the connection's defaultEncoding for all string operations 
				returning.
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
                connection
    @discussion The default setting is NSMacOSRoman.  While this default is 
				used to maintain existing functionality, this will be changed 
				NSUTF8StringEncoding when PostgreSQL9 is released.
	@param      value the defaultEncoding as an NSSTringEncoding ( 
			    http://developer.apple.com/mac/library/documentation/Cocoa/Reference/Foundation/Classes/NSString_Class/Reference/NSString.html#//apple_ref/doc/c_ref/NSStringEncoding )

    @result     void
*/
-(void)setDefaultEncoding:(NSStringEncoding)value;
	
/*!
    @method     
    @abstract   Provide a text based error (or information) about the status 
				of the last command.  
    @discussion Most of the execution methods of the Connection will set this
				value to either nil or a string that contains the last error or
				any messages returned by the server associated with the command.
				
				The returns messages are not always errors.  The may simply be 
				notes regarded the execution of the command from the server that 
				do not impact the result set itself.
*/
-(NSString *)lastCmdStatus;

#pragma mark -
#pragma mark Exported Constants

/*!
    @const 
    @abstract   Notification for use with async connections being established.
    @discussion <#(description)#>
*/
FOUNDATION_EXPORT NSString * const PGSQLConnectionDidCompleteNotification;
/*!
	 @const 
	 @abstract   Notification for use with async command processing.
	 @discussion <#(description)#>
 */
FOUNDATION_EXPORT NSString * const PGSQLCommandDidCompleteNotification;	

@end


static PGSQLConnection *globalPGSQLConnection;
#pragma unused(globalPGSQLConnection)