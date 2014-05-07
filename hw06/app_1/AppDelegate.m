CGRect viewRect = [[UIScreen mainScreen] bounds];
self.window = [[UIWindow alloc] initWithFrame:viewRect];

self.viewController = [[ViewController alloc] init];
self.window.rootViewController = self.viewController;
[self.window makeKeyAndVisible];