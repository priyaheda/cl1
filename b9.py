import math
import operator
import collections

def idf(word,allDocuments):
	noofdocumentswiththisterm=0
	for cnt in allDocuments:
		if word in cnt:
			noofdocumentswiththisterm=noofdocumentswiththisterm+1
	if noofdocumentswiththisterm>0 :
		return round(math.log(float(float(len(allDocuments))/float(noofdocumentswiththisterm)),2),3)
	else:
		return 0



def tf(word,document):
	return document.count(word)

def caltfidf(term,document):
	return tf(term,document)*idf(term,terms)

def cosinesimilarity(q,x,fin_terms):
	a=0
	for word in fin_terms:
		a=a+caltfidf(word,q)*caltfidf(word,x)

	b=0
	b=denom_cosinesim(q,fin_terms)*denom_cosinesim(x,fin_terms)

	if(not b):
		return 0
	else:
		return(round(a/b,3))

def denom_cosinesim(document,fin_terms):
	val=0
	for word in fin_terms:
		val+=(pow(caltfidf(word,document),2))

	return math.sqrt(val)
	



terms=[]
fin_terms=[]
k=3
f=[]
doc=['doc1.txt','doc2.txt','doc3.txt','doc4.txt','doc5.txt','doc6.txt']
dataset=[['doc1.txt','animals'],['doc2.txt','animals'],['doc3.txt','animals'],['doc4.txt','sports'],['doc5.txt','sports'],['doc6.txt','sports']]

for x in doc:
	f.append(open(x,'r').read())

for x in f:
	terms.append(x.lower().rstrip('\n'))

for x in terms:
	fin_terms=fin_terms+x.split()
fin_terms=set(fin_terms)
fin_terms=list(fin_terms)

testf=input("Enter the test file")
q=open(testf,'r').readline().lower()

cnt=0
for x in terms:
	dataset[cnt]=dataset[cnt]+[cosinesimilarity(q,x,fin_terms)]
	cnt=cnt+1

print("Cosine similarity values are:")
print dataset

sortedDataset=sorted(dataset,key=operator.itemgetter(2),reverse=True)
top_k=sortedDataset[:k]
top_k[:]=(x for x in top_k if x[2]!=0)

if(not (len(top_k))):
	print ("No match found! \n")

else:
	class_count=collections.Counter(category for (document,category,value) in top_k).most_common(1)
	print (class_count)
	print("Class of file is: "+class_count[0][0])


	



