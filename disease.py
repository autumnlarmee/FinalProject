import csv
import numpy as np
import pandas as pd
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

data = pd.read_csv("patientdata.csv")
#X features and y target variable
y = data.TenYearCHD.values
#normalization
x_data = data.drop(["TenYearCHD"], axis=1)
x=(x_data-np.min(x_data)) / (np.max(x_data) - np.min(x_data))

#train test split
from sklearn.model_selection import train_test_split
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.15, random_state=42)

from sklearn.tree import DecisionTreeClassifier
dt = DecisionTreeClassifier()
dt.fit(x_train, y_train)
print("score: ", dt.score(x_test, y_test))

#ask user to input information
userInput = []
iName = input("Enter name: ")
userInput.append(int(input("M or F? (Enter 1 or 0): ")))
userInput.append(int(input("Enter age: ")))
userInput.append(int(input("Enter education level (1-4): ")))
userInput.append(int(input("Are you a current smoker? Enter 1 or 0: ")))
userInput.append(int(input("How many cigs do you smoke per day? ")))
userInput.append(int(input("Are you on blood pressure meds? (enter 1 or 0): ")))
userInput.append(int(input("Do you have prevalent strokes? (enter 1 or 0): ")))
userInput.append(int(input("Do you have prevalent hypertension? (enter 1 or 0): ")))
userInput.append(int(input("Do you have diabetes? (enter 1 or 0): ")))
userInput.append(float(input("What is your total cholesterol? (50-400): ")))
userInput.append(float(input("What is your systolic blood pressure? (50-200): ")))
userInput.append(float(input("What is your diastolic blood pressure? (40-200): ")))
userInput.append(float(input("What is your body mass index? (15-50): ")))
userInput.append(float(input("What is your heart rate? (20-200): ")))
userInput.append(float(input("What is your glucose level? (50-200): ")))

#convert user input to a DataFrame
userData = pd.DataFrame([userInput], columns = x_data.columns)

#normalize userData
userX = (userData - np.min(x_data)) / (np.max(x_data) - np.min(x_data))

#make prediction and output result
print("Predicting chances of coronary heart disease within the next 10 years...\n")
prediction = dt.predict(userX)
if prediction[0] == 1:
    print("You have a high chance of coronary heart disease.")
else:
    print("You have a low chance of coronary heart disease.")
