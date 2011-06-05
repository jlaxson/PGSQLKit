//
//  PGSQLColumn.m
//  PGSQLKit
//
//  Created by Andy Satori on 6/7/07.
//  Copyright 2007 Druware Software Designs. All rights reserved.
//

#import "PGSQLColumn.h"
#include "libpq-fe.h"

@implementation PGSQLColumn

-(id)initWithResult:(void *)result atIndex:(int)columnIndex
{	
    [super init];
	
	index = columnIndex;
	name = [[NSString alloc] initWithCString:PQfname(result, columnIndex)];
	type = PQftype(result, columnIndex);
	size = PQfsize(result, columnIndex);
	offset = PQfmod(result, columnIndex);
	
	return self;
}

- (void)dealloc
{
	[name release];
	[super dealloc];
}

- (NSString *)name
{
    return [[name retain] autorelease];
}

-(int)index
{
	return index;
}

-(int)type;
{
	return type;
}

-(int)size
{
	return size;
}

-(int)offset
{
	return offset;
}

@end

