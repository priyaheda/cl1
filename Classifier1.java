import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Random;

import weka.classifiers.Evaluation;
import weka.classifiers.trees.J48;
import weka.core.Instances;

public class Classifier1 {
	public static void main(String args[]) throws Exception
	{
		BufferedReader br = new BufferedReader(new FileReader("/home/priya/workspace/B11/src/test.arff"));
		Instances train = new Instances(br);
		train.setClassIndex(train.numAttributes()-1);
		
		br = new BufferedReader(new FileReader("/home/priya/workspace/B11/src/test.arff"));
		Instances test = new Instances(br);
		test.setClassIndex(test.numAttributes()-1);
		
		J48 tree = new J48();
		tree.setOptions(null);
		tree.buildClassifier(train);
		Evaluation eval = new Evaluation(train);
		eval.evaluateModel(tree,test);
		System.out.println(eval.toSummaryString(false));
		System.out.println(eval.toMatrixString());
		System.out.println(eval.toClassDetailsString());
	}
}