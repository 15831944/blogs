AppDelegate and ViewController both define classes, but the classes are used for different things. 

# ViewController

ViewController.h/m define a view controller class that manages a hierarchy of views -- basically, one screen of an application. 

You might have multiple screens that each have their own view controller.

# AppDelegate

AppDelegate.h/m define a class that manages the application overall. 

The app will create one instance of that class and send that object messages that let the delegate influence the app's behavior at well-defined times. 

For example, -application:didFinishLaunchingWithOptions: is sent when the app has finished launching and is ready to do something interesting. 

Take a look at the UIApplicationDelegate reference page for a list of messages that the app delegate can implement to modify the behavior of the application.

If care is not taken, the AppDelegate could easily become one of the most accessed objects in the application.

I usually refrain from calling methods in the AppDelegate from any of my ViewControllers. 
 
Unless, something needs to be reported to the AppDelegate that would influence the behaviour of the whole application.

I keep my AppDelegate for the following:

1. initialization: whatever needs to be done on the very first launch (after an install or an update)

2. data migration from version to version (e.g. if you use CoreData and migrations)

3. configuration of objects linked via IBOutlets from MainWindow.xib

4. determining the initial orientation to launch in

5. saving uncommitted data / state prior to the application being terminated or entering background mode

6. registering for the Apple Push Notification Service and sending the device token to our server

7. opening one of the supported application URLs (e.g. maps://)

For other use case scenarios and a more thourough description of the AppDelegate, see the iOS Application Programming Guide.

+1 for pointing out the peril of the app delegate. Some people use it to do all kinds of things, mainly because it's a singleton and therefore easy to access globally. I don't think that's a good approach.

The view-controller. h/m is responsible of controlling the connection between your model and your view.

AppDelegate. h/m is responsible for the life-cycle of your application. What to do when the user press the home button and exit your app, what to do when the app enter background. Things like this.

Speaking about the life-cycle, declaring global variables that the app need to use in different viewcontrollers must be on the AppDelegate file.
