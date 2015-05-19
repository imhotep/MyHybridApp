# MyHybridApp
iOS Cordova WebView Example

Combine Web Controls with Native controls

Steps to recreate:

- Run the following command:

```bash
cordova-ios/bin/create MyApp org.example.myapp MyApp
```

- Select Classes then click on File -> New -> File -> User Interface name it `Main.storyboard`.

- Select the root of your project and then
    - Under deployment info. Change Devices to iPhone
    - Change Main Interface to `Main.storyboard`
- Run
- Remove everything from `didLaunchWithOptions` in `AppDelegate.m` except for "return YES"
- Select the Cordova scene in the Storyboard and change the view controller to `MainViewController` in the identity inspector.
- Change Bar Item title to 'Cordova'
- Change Image to icon-40.png
- Change Bar Item in the other Scene
- Click on Classes. Then click on File -> New -> File -> Source -> Cocoa Touch Class
- Class: Type in `MyTableViewController` Subclass of `UITableViewController`
- Go back to storyboard and add TableViewController to the second scene. Also add a tableview to replace the view.
- Run
- Go back to the storyboard and select the second scene's controller and change it to `MyTableViewController`
- Go to `MyTableViewController.h` and add this property to the interface

```objc
@property (nonatomic,strong) NSMutableArray* bookmarks;
```

- Go to `MyTableViewController.m` and add this line in `viewDidLoad`

```objc
self.bookmarks = [NSMutableArray array];
```

- change `numberOfSectionsInTableView` method to "return 1"
- add this code in `cellForRowAtIndexPath`
```objc
UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"Cell1" forIndexPath:indexPath];

cell.textLabel.text = [self.bookmarks objectAtIndex:indexPath.row];

return cell;
```
- Select Classes and then Click on File -> New -> File -> iOS - Source -> Cocoa Touch Class
- Enter `MyHybridPlugin` in Class and select `CDVPlugin` in `Subclass of` and follow the steps
- Go to `MyHybridPlugin.h`, import `<Cordova/CDVPlugin.h>` and add this method
```objc
-(void)addBookmark:(CDVInvokedUrlCommand*) command;
```
- Go to `MyHybridPlugin.m` and add this code
```objc
-(void)addBookmark:(CDVInvokedUrlCommand*) command {

    NSString* bookmark = [command.arguments objectAtIndex:0];

    if(bookmark) {
        NSLog(@"addBookmark %@", bookmark);
        MainViewController* mvc = (MainViewController*)[self viewController];

        MyTableViewController* tvc = (MyTableViewController*)mvc.tabBarController.viewControllers[1];
        [tvc.bookmarks addObject:bookmark];
        [tvc.tableView reloadData];
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    } else {
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }
}
```

- go to www/index.html and add these lines just under the `<div id="deviceready">` 

```HTML
<label for="bookmark">Bookmark</label>
<input id="bookmark" type="text" />
<button id="bookmarkBtn">Add a bookmark</button>
```

- go to www/js/index.js to the app object

```javascript
addBookmark: function() {
    var win = function(d) {
        console.log("Bookmark added!");
    };
    var fail = function(e) {
        console.log(e)
    }
    var bookmark = document.getElementById("bookmark").value;
    cordova.exec(win, fail, "MyHybridPlugin", "addBookmark", [bookmark]);
}
```

- open config.xml and add a reference to our plugin
```XML
<feature name="MyHybridPlugin">
    <param name="ios-package" value="MyHybridPlugin" />
</feature>
```
