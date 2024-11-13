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
