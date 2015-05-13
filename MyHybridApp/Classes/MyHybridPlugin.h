//
//  MyHybridPlugin.h
//  MyHybridApp
//
//  Created by Anis Kadri on 5/13/15.
//
//

#import <Cordova/CDVPlugin.h>

@interface MyHybridPlugin : CDVPlugin
    - (void)addBookmark:(CDVInvokedUrlCommand*) command;
@end
