import csv
import numpy as np
import pandas as pd
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

data = pd.read_csv("cleandata.csv")
#X features and y target variable
y = data.TenYearCHD.values
#normalization
x_data = data.drop(["TenYearCHD"], axis=1)
x=(x_data-np.min(x_data)) / (np.max(x_data) - np.min(x_data))

#train test split
from sklearn.model_selection import train_test_split
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.15, random_state=42)

from sklearn.tree import DecisionTreeRegressor
dt = DecisionTreeRegressor(min_samples_leaf=15, random_state=42)
print("Please wait while I construct regression tree to be used for predictions...")
dt.fit(x_train, y_train)
print("...Done")
#print("score: ", dt.score(x_test, y_test))

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

# Calculate risk score
riskScore = dt.predict(userX)[0] * 100
print(f"\nRisk Score: {riskScore:.0f}% chance of developing Coronary Artery Disease within the next 10 years.")
