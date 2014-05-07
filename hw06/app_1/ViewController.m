#import "ViewController.h"

@implementation ViewController

- (void)viewDidLoad
{
  [super viewDidLoad];
}

- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
   self.view.alpha = ((double)arc4random() / 0x100000000);
}
@end