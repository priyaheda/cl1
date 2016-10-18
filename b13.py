import operator
import random
import csv
import math

def loadDataSet(filename,split,trainingSet=[],testSet=[]):
	with open (filename,'rb') as csvfile:
		lines=csv.reader(csvfile)
		dataset=list(lines)
		for x in range(len(dataset)-2):
			for y in range(4):
				dataset[x][y]=float(dataset[x][y])
			
			if random.random()<split:
				trainingSet.append(dataset[x])
			else:
				testSet.append(dataset[x])

def eucledianDistance(instance1,instance2,length):
	distance=0;
	for x in range(length):
		distance+=pow((instance1[x]-instance2[x]),2)
	return math.sqrt(distance)

def getneighbours(trainingSet,testInstance,k):
	distances=[]
	neighbours=[]
	length=(len(testInstance)-1)
	for x in range(len(trainingSet)):
		dist=eucledianDistance(trainingSet[x],testInstance,k)
		distances.append((trainingSet[x],dist))

	distances.sort(key=operator.itemgetter(1))
	for x in range(k):
		neighbours.append(distances[x][0])

	return (neighbours)

def getResponse(neighbours):
	classVotes={}
	for x in range(len(neighbours)):
		response=neighbours[x][-1]
		if response in classVotes:
			classVotes[response]+=1
		else:
			classVotes[response]=1
	sortedVotes=sorted( classVotes.iteritems(),key=operator.itemgetter(1),reverse=True)
	return sortedVotes[0][0]

def getaccuracy(predictions,testSet):
	correct=0
	for x in range(len(testSet)):
		if(predictions[x]==testSet[x][-1]):
			correct+=1

	return (correct/float(len(testSet)))*100

def main():
	trainingSet=[]
	testSet=[]
	predictions=[]
	split=0.67
	k=3
	loadDataSet('iris.data',split,trainingSet,testSet)
	print ("Training Data: "+ repr(len(trainingSet)))
	print ("Test Data: "+ repr(len(testSet)))
	for x in range(len(testSet)):
		neighbours=getneighbours(trainingSet,testSet[x],k)
		result=getResponse(neighbours)
		predictions.append(result)
		print ("Predicted: "+repr(result)+"	Actual: "+repr(testSet[x][-1]))

	accuracy=getaccuracy(predictions,testSet)
	print ("Accuracy is: "+repr(accuracy)+" %")

main()
		
