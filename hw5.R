install.packages('caret')
library(caret)

# seed for randomness (might be unnecessary)
set.seed(777)

# get data from csv
voters <-  read.csv("test.data", header=FALSE, sep=",")

# training config
df <- data.frame(laplace=1, usekernel=c(FALSE,TRUE),adjust=1)

# setup 10-fold
ct <- trainControl(method = "cv", number = 10)

# train model with 10 fold as control
model <- train(V1~.,data=voters, method = "naive_bayes", trControl = ct, tuneGrid = df)

# show accuracy per attempt
model$resample

# show total accuracy 
model
