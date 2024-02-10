#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.

// Robot configuration code.
motor LeftTrainMotorA = motor(PORT10, ratio18_1, false);
motor LeftTrainMotorB = motor(PORT9, ratio18_1, false);
motor_group LeftTrain = motor_group(LeftTrainMotorA, LeftTrainMotorB);

motor RightTrainMotorA = motor(PORT8, ratio18_1, false);
motor RightTrainMotorB = motor(PORT7, ratio18_1, false);
motor_group RightTrain = motor_group(RightTrainMotorA, RightTrainMotorB);
motor LeftWing = motor(PORT5, ratio18_1, true);

motor RightWing = motor(PORT6, ratio18_1, false);

controller Controller1 = controller(primary);



// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}



// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling Train based on controller inputs
bool Controller1LeftShoulderControlTrainStopped = true;
bool Controller1RightShoulderControlTrainStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the Train based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // check the ButtonL1/ButtonL2 status to control LeftWing
      if (Controller1.ButtonL1.pressing()) {
        LeftWing.spin(forward);
        Controller1LeftShoulderControlTrainStopped = false;
      } else if (Controller1.ButtonL2.pressing()) {
        LeftWing.spin(reverse);
        Controller1LeftShoulderControlTrainStopped = false;
      } else if (!Controller1LeftShoulderControlTrainStopped) {
        LeftWing.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1LeftShoulderControlTrainStopped = true;
      }
      // check the ButtonR1/ButtonR2 status to control RightWing
      if (Controller1.ButtonR1.pressing()) {
        RightWing.spin(forward);
        Controller1RightShoulderControlTrainStopped = false;
      } else if (Controller1.ButtonR2.pressing()) {
        RightWing.spin(reverse);
        Controller1RightShoulderControlTrainStopped = false;
      } else if (!Controller1RightShoulderControlTrainStopped) {
        RightWing.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1RightShoulderControlTrainStopped = true;
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);

#pragma endregion VEXcode Generated Robot Configuration
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Authors:      hunt/willam                                               */
/*    Created:      1/30/2024, 9:34:37 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
// Make sure all required headers are included.

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;


// A global instance of competition
competition Competition;

// define your global instances of Train and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  LeftWing.setStopping(hold);
  RightWing.setStopping(hold);

  LeftTrain.setStopping(brake);
  RightTrain.setStopping(brake);

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

//custom right wing movement (IE impliments stops)
void moveLeftWing(int toDegrees, double error, int speed)
{
  LeftWing.setVelocity(speed, percent);

  while (
    LeftWing.position(degrees) < toDegrees - error ||
    LeftWing.position(degrees) > toDegrees + error)
  {
    if (LeftWing.position(degrees) < toDegrees - error)
    {
      LeftWing.spin(forward);
    }
    else if (LeftWing.position(degrees) > toDegrees + error)
    {
      LeftWing.spin(reverse);
    }
    else
    {
      LeftWing.stop();
    }
  }

  LeftWing.stop();
}

//custom right wing movement (IE impliments stops)
void moveRightWing(int toDegrees, double error, int speed)
{
  RightWing.setVelocity(speed, percent);

  while (
    RightWing.position(degrees) < toDegrees - error ||
    RightWing.position(degrees) > toDegrees + error)
  {
    if (RightWing.position(degrees) < toDegrees - error)
    {
      RightWing.spin(forward);
    }
    else if (RightWing.position(degrees) > toDegrees + error)
    {
      RightWing.spin(reverse);
    }
    else
    {
      RightWing.stop();
    }
  }

  RightWing.stop();
}

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  LeftWing.setStopping(hold);
  RightWing.setStopping(hold);

  LeftTrain.setStopping(brake);
  RightTrain.setStopping(brake);

  //moveRightWing(-135, 0.5, 10);
  //moveLeftWing(-135, 0.5, 10);


  LeftWing.spin(reverse);
  wait(800, msec);
  RightWing.spin(reverse);
  wait(800, msec);


  wait(200, msec);

  //LeftTrain.setVelocity(30, percent);
  //RightTrain.setVelocity(30, percent);

  LeftTrain.spin(forward);
  RightTrain.spin(forward);

  wait(8000, msec);

  LeftTrain.stop();
  RightTrain.stop();

  //moveRightWing(0, 0.5, 20);

  wait(800, msec);

  //moveRightWing(90, 0.5, 10);
  //moveLeftWing(0, 0.5, 20);
  //moveRightWing(0, 0.5, 20);

  RightWing.spin(forward);
  wait(800, msec);
  LeftWing.spin(forward);
  wait(800, msec);
  
  wait(100, msec);

  LeftTrain.setVelocity(20, percent);
  RightTrain.setVelocity(40, percent);

  LeftTrain.spin(forward);
  RightTrain.spin(forward);

  wait(1000, msec);

  LeftTrain.stop();
  RightTrain.stop();

  wait(200, msec);

  LeftTrain.setVelocity(100, percent);
  RightTrain.setVelocity(100, percent);

  LeftTrain.spin(forward);
  RightTrain.spin(forward);

  wait(1500, msec);

  LeftTrain.setVelocity(30, percent);
  RightTrain.setVelocity(30, percent);

  LeftTrain.spin(reverse);
  RightTrain.spin(reverse);

  wait(1500, msec);

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your Train, etc.
    // ........................................................................
    int leftRight = Controller1.Axis3.position();
    int upDown = Controller1.Axis1.position();
    
    double leftVelocity, rightVelocity;
    
    leftVelocity = ((upDown + leftRight) / 2)*2;
    rightVelocity = ((upDown - leftRight) / 2)*2;

    LeftTrain.setVelocity(leftVelocity, percent);
    RightTrain.setVelocity(rightVelocity, percent);

    LeftTrain.spin(forward);
    RightTrain.spin(forward);


    

    
  
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  pre_auton();
  bool meow = true;
  if (meow == true){
    autonomous();

  }
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  
  

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
