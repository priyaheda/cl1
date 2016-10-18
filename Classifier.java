import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Random;

import weka.classifiers.Evaluation;
import weka.classifiers.bayes.NaiveBayes;
import weka.core.Instances;

public class Classifier {
	public static void main(String args[]) throws Exception
	{
		BufferedReader br = new BufferedReader(new FileReader("/home/priya/workspace/B11/src/test.arff"));
		Instances train = new Instances(br);
		train.setClassIndex(train.numAttributes()-1);
		
		NaiveBayes nb = new NaiveBayes();
		nb.buildClassifier(train);
		Evaluation eval = new Evaluation(train);
		eval.crossValidateModel(nb, train, 10, new Random(1));
		System.out.println(eval.toSummaryString());
		System.out.println(eval.toMatrixString());
		System.out.println(eval.toClassDetailsString());
		
	}
}