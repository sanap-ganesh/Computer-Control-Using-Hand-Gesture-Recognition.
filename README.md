
### Gesture Keyboard Library

Now that everything is working, let's dive into the library.
While a Dataset is already included, you should create a new one for a few reasons:
* Every device is different, even a small change in the accelerometer position makes the device less precise. **Everytime you change your device you should create a new dataset, to improve precision.**
* If you want to change or add gestures, you have add new data to the dataset.

#### Working with the Dataset

Start by deleting the content of the `data` folder, we will replace it with a newly created dataset.

This library was originally conceived to make a keyboard, so each gesture is associated with a character ( case sensitive ). This means that you can teach the algorithm a maximum of about 60 different gestures.

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
