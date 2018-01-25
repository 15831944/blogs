//
//  ICFGravityViewController.m
//  Dynamics
//
//  Created by Kyle Richter on 7/14/13.
//  Copyright (c) 2013 Kyle Richter. All rights reserved.
//

#import "ICFGravityViewController.h"

@interface ICFGravityViewController ()

@end

@implementation ICFGravityViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
 
    animator = [[UIDynamicAnimator alloc] initWithReferenceView:self.view];
    UIGravityBehavior* gravityBeahvior = [[UIGravityBehavior alloc] initWithItems:@[frogImageView]];
    [gravityBeahvior setGravityDirection:CGVectorMake(0.0f, 0.1f)]; //property changed after printing of the book
    [animator addBehavior:gravityBeahvior];
}


@end
