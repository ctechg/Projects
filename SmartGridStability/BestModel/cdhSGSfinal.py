#!/usr/bin/env python
# coding: utf-8

# In[2]:


import jsonify
import requests
import pickle
import sys
import os
import re
import sklearn
import joblib
from joblib import load
from flask import Flask, render_template, url_for, flash, redirect, request, send_from_directory
from sklearn.preprocessing import StandardScaler
import tensorflow
from tensorflow.keras.models import load_model
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import os
import tensorflow as tf
import h5py
get_ipython().run_line_magic('matplotlib', 'inline')
import warnings                       
warnings.filterwarnings("ignore")
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import confusion_matrix
from sklearn.model_selection import KFold
from sklearn.model_selection import train_test_split
from keras.models import Sequential
from keras.layers import Dense
from keras.models import load_model
from datetime import datetime


# In[2]:


#from google.colab import drive
#drive.mount('/content/gdrive')
#os.chdir('gdrive/My Drive/kaggle/SmartGrid')


# In[3]:


#df = pd.read_csv("data/Data_for_UCI_named.csv")
#df.head(10)


# In[4]:


# from google.colab import files
# uploaded = files.upload()

# for name, data in uploaded.items():
#   with open(name, 'wb') as f:
#     f.write(data)
#     print ('saved file', name)


# In[5]:


#import io
#df = pd.read_csv(io.BytesIO(uploaded['Data_for_UCI_named.csv']))


# In[3]:


df = pd.read_csv("Data_for_UCI_named.csv")


# In[7]:


df.head(10)


# In[8]:


df.info()


# In[9]:


df.describe()


# In[10]:


print("\nTotal unique labels : ", df['stabf'].nunique())
print(df['stabf'].value_counts())

sns.set_style('whitegrid')
sns.countplot(x='stabf',data=df)


# In[11]:


plt.figure(figsize=(8,4))
sns.distplot(df['stab'], color='g')


# In[12]:


plt.figure(figsize=(14,10))
sns.heatmap(df.corr(), annot=True, cmap='coolwarm_r')


# In[4]:


sns.set()
start_time = datetime.now()

data = df.copy()

map1 = {'unstable': 0, 'stable': 1}
data['stabf'] = data['stabf'].replace(map1)


# In[14]:


#X = data.drop(['stab', 'stabf'],axis=1)
#Y = data['stab']


# In[15]:


data.head()


# In[16]:



#X_train, X_test, Y_train, Y_test = train_test_split(X,Y,test_size=0.2,random_state=50)
#X_val, X_test, Y_val, Y_test = train_test_split(X_test,Y_test,test_size=0.5,random_state=50)


# In[5]:


X = data.iloc[:, :12]
y = data.iloc[:, 13]

X_training = X.iloc[:9000, :]
y_training = y.iloc[:9000]

X_testing = X.iloc[9000:, :]
y_testing = y.iloc[9000:]


# In[18]:


#X_testing.iloc[:,:]


# In[6]:


X_training = X_training.values
y_training = y_training.values

X_testing = X_testing.values
y_testing = y_testing.values


# In[7]:


scaler = StandardScaler()
X_training = scaler.fit_transform(X_training)
X_testing = scaler.transform(X_testing)


# In[38]:


joblib.dump(scaler, 'Scaler.joblib')


# In[22]:


# ANN initialization
model = Sequential()

# Input layer and first hidden layer
model.add(Dense(units = 240, kernel_initializer = 'uniform', activation = 'relu', input_dim = 12))

# Second hidden layer
model.add(Dense(units = 48, kernel_initializer = 'uniform', activation = 'relu'))

# Third hidden layer
model.add(Dense(units = 12, kernel_initializer = 'uniform', activation = 'relu'))

# Single-node output layer
model.add(Dense(units = 1, kernel_initializer = 'uniform', activation = 'sigmoid'))

# ANN compilation
model.compile(optimizer = 'adam', loss = 'binary_crossentropy', metrics = ['accuracy'])


# In[23]:


cross_val_round = 1
print(f'Model evaluation\n')

for train_index, val_index in KFold(15, shuffle=True, random_state=10).split(X_training):
    x_train, x_val = X_training[train_index], X_training[val_index]
    y_train ,y_val = y_training[train_index], y_training[val_index]
    model.fit(x_train, y_train, epochs=100, verbose=0)
    model_loss, model_accuracy = model.evaluate(x_val, y_val)
    print(f'Round {cross_val_round} - Loss: {model_loss:.4f} | Accuracy: {model_accuracy * 100:.2f} %')
    cross_val_round += 1


# In[24]:


#X_testing[0].reshape(1,12).shape


# In[12]:


y_pred = model.predict(X_testing)
#print(y_pred)
y_pred[y_pred <= 0.5] = 0
y_pred[y_pred > 0.5] = 1


# In[26]:


# li = list(np.unique(y_pred))
# for i in li:
#     print(round(i,2))
# li = y_pred
# j = 9002
# for i in li:
#     if i[0]>0.8 and i[0]<0.9:
#         print(j,round(i[0],5))
#     j+=1


# In[27]:


cm = pd.DataFrame(data=confusion_matrix(y_testing, y_pred, labels=[0, 1]),
                  index=["Actual Unstable", "Actual Stable"],
                  columns=["Predicted Unstable", "Predicted Stable"])
cm


# In[37]:


#model.save('SG24048121_1.h5')
model.save('Model.h5')


# In[8]:


model= load_model('Model.h5')
scaler=load('Scaler.joblib')


# In[9]:



print(model.summary())


# In[10]:


model.get_weights() 


# In[46]:


# li = []
# j=9002
# for i in range(0,1000):
#     if y_testing[i]!=y_pred[i]:
#         print(y_testing[i],y_pred[i], j+i)
#         li.append(i)
# li


# In[40]:


def calcres(t1, t2, t3, t4, p1, p2, p3, p4, g1, g2, g3, g4):
    X_test = scaler.transform([[t1, t2, t3, t4, p1, p2, p3, p4, g1, g2, g3, g4]])
    #print(X_test,X_test.shape)
    prediction = model.predict(X_test)
    print(prediction)
    if prediction<=0.5:
        print( "Oops! the system is linearly unstable.")
    else:
        print( "Great! the system is stable." )


# In[42]:


calcres(2.837221501,8.244192067,0.724832379,9.398787417,2.686927371,-0.836726338,-0.956175486,-0.894025548,0.799332056,0.095360039,0.251985331,0.153553754)
calcres(8.472177282,2.045812588,2.550468814,9.855937949,3.635816965,-0.990384574,-0.782448796,-1.862983596,0.758596065,0.294628154,0.216889989,0.48657837)

