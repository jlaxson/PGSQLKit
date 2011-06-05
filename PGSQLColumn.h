//
//  PGSQLColumn.h
//  PGSQLKit
//
//  Created by Andy Satori on 6/7/07.
//  Copyright 2007 Druware Software Designs. All rights reserved.
//

//#import <Cocoa/Cocoa.h>

@interface PGSQLColumn : NSObject {
	NSString *name;
	int index;
	int type;
	int size;
	int offset;
}

-(id)initWithResult:(void *)result atIndex:(int)columnIndex;

-(NSString *)name;
-(int)index;
-(int)type;
-(int)size;
-(int)offset;

@end
