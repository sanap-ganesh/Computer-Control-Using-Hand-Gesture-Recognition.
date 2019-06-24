Computer Control Using Hand Gesture Recognition has 2 modules:-
1. Mouse Control
2. Keyboard Control.

Let's start a new recording batch, where you will record new samples for a specific gesture.
Open the terminal and write:

```
python start.py target=a:0 port=COM3
```

Explanation:
* The "target" argument tells the module that we want to record new samples for a specific gesture.
* The "a" character is the one that characterize a gesture, it must be unique for every gesture and it must have a length of 1.
* The "0" character is the *batch number*, it must be different every time you register a new batch to avoid sample overriding. For example, the first time you record a batch set it to 0, the next time 1 and so on.
* The "port" represents the serial port your Arduino is connected to.

When start.py is running, you will record different samples by pushing and relasing the integrated button on the Arduino. When the button is pressed, the library records the data from the accelerometer. For each gesture, a good number of samples is 40.

Every sample get saved as a different file in the data folder.

### Train the Model

When your dataset is ready, you can use it to train the machine learning algorithm. This is pretty straightforward, open the terminal and write:

```
python learn.py
```

#### In case of problems:
If you have problems with the library "model_selection", you have to upgrade your Sklearn dependency. 
Try to use the command: `pip install --upgrade sklearn`.

### Use the model

To check out if the model is working, open the terminal and write:

```
python start.py port=<YOUR_SERIAL_PORT> predict
```

Now you can make gestures and see the algorithm predicting the correct one, most of the times :)
