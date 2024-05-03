# CSE251

This repo contains my solutions for all labs and projects in [CSE251](https://www.cse.msu.edu/~cse251/). However, **do note that I may not follow the instructions exactly and implement some features in ways I find interesting**.

## Usage
The entry point to compile and run any solution is `./run.sh`. Some examples are as follows:
```shell
$ ./run.sh project-1
```
```shell
$ ./run.sh step-4 factorial
```
```shell
$ ./run.sh project-2 eval-speed
```

## Environment Prerequisites
Some labs and projects require X-Server and wxWidgets, but I am using a Mac. My solutions make use of Docker and `xquartz` app to emulate the environment (credit to [this blog post](http://mamykin.com/posts/running-x-apps-on-mac-with-docker/)).

Do note that because of this, **I can only ensure these solutions work on Mac**.

Set-up steps:
1. Install Docker
2. Install `xquartz`
   ```shell
   $ brew install --cask xquartz
   ```
3. Reboot machine
4. Open `xquartz` and run
   ```shell
   $ xhost +localhost
   ```

## More on Project 2

### Evaluate PID Controller
I have added a separate `eval-speed.c` file to evaluate the PID controller as suggested in the project instructions. Because the instruction is not clear on which loading should I evaluate the PID controller on, I write this program to **run the elevator up and down for all types of loadings** and compute the score.

The best result I achieve (using the same parameters as committed)
```shell
$ [load=0] Average speed up: 1.001103
$ [load=0] Average speed down: -0.999055
$ [load=0] Maximum speed: 1.003662
$ [load=0] Result: 0.000005
$ [load=0] Maximum speed up: 1.002109
$ [load=0] Maximum speed down: -1.000012
$ 
$ [load=1] Average speed up: 1.001165
$ [load=1] Average speed down: -0.998933
$ [load=1] Maximum speed: 1.003696
$ [load=1] Result: 0.000006
$ [load=1] Maximum speed up: 1.003696
$ [load=1] Maximum speed down: -0.999695
$ 
$ [load=2] Average speed up: 1.000500
$ [load=2] Average speed down: -0.999361
$ [load=2] Maximum speed: 1.002401
$ [load=2] Result: 0.000002
$ [load=2] Maximum speed up: 1.001804
$ [load=2] Maximum speed down: -1.001875
$ 
$ [load=3] Average speed up: 1.000099
$ [load=3] Average speed down: -1.000065
$ [load=3] Maximum speed: 1.002389
$ [load=3] Result: 0.000000
$ [load=3] Maximum speed up: 1.002371
$ [load=3] Maximum speed down: -1.002332
$ 
$ [load=4] Average speed up: 0.999946
$ [load=4] Average speed down: -0.999997
$ [load=4] Maximum speed: -1.002463
$ [load=4] Result: 0.000000
$ [load=4] Maximum speed up: 1.002265
$ [load=4] Maximum speed down: -1.002463
$ 
$ [load=5] Average speed up: 0.999617
$ [load=5] Average speed down: -1.000396
$ [load=5] Maximum speed: -1.002623
$ [load=5] Result: 0.000001
$ [load=5] Maximum speed up: 1.001715
$ [load=5] Maximum speed down: -1.002341
$ 
$ [load=6] Average speed up: 0.999345
$ [load=6] Average speed down: -1.000928
$ [load=6] Maximum speed: -1.003103
$ [load=6] Result: 0.000003
$ [load=6] Maximum speed up: 1.001343
$ [load=6] Maximum speed down: -1.003103
$ 
$ [load=7] Average speed up: 0.998981
$ [load=7] Average speed down: -1.001180
$ [load=7] Maximum speed: -1.003154
$ [load=7] Result: 0.000005
$ [load=7] Maximum speed up: 1.000738
$ [load=7] Maximum speed down: -1.003132
$ 
$ [total] Average speed up: 1.000094
$ [total] Average speed down: -0.999989
$ [total] Maximum speed: 1.003696
$ [total] Result: 0.000000
$ [total] Maximum speed up: 1.003696
$ [total] Maximum speed down: -1.003132
```

### "Bug Fix"

When I run the reference solution, I find that the elevator will never reach the first floor if you just repeat the following:
1. Press the level 3 panel button.
2. After the elevator reaches floor 3, press level 2 panel button
3. Before the elevator stops at level 2, press up call buttons of both level 1 and level 2.
4. Wait for the elevator to reach the second floor.

You will see:
1. The up call light on level 2 is turned off after step 4.
2. The elevator goes up to level 3 after the following step 1. 

However, the expected behavior is 
- After step 4, the elevator should continue to descend to level 1 - The up call button at level 2 keeps on until the elevator ascends from level 1 and stops at level 2 again. 

I achieve this desired behavior in my own solution.
