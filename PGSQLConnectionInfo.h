//
//  PGSQLConnectionInfo.h
//  PGSQLKit
//
//  Created by Andy Satori on 4/21/09.
//  Copyright 2009 Druware Software Designs. All rights reserved.
//

// #import <Cocoa/Cocoa.h>
#import "PGSQLConnection.h"

@interface PGSQLConnectionInfo : NSObject {
	PGSQLConnection			*pgConnection;

	NSString *versionString;
}

-(id)initWithConnection:(PGSQLConnection *)connection;
- (NSString *)versionString;

@end
