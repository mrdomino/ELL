////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  EMLL
//  File:     SortingTreeLearner.tcc (trainers)
//  Authors:  Ofer Dekel
//
//  [copyright]
//
////////////////////////////////////////////////////////////////////////////////////////////////////

// dataset
#include "RowDataset.h"
#include "DenseDataVector.h"

namespace trainers
{    
    template <typename LossFunctionType>
    SortingTreeLearner<LossFunctionType>::SortingTreeLearner(LossFunctionType lossFunction) : _lossFunction(lossFunction)
    {}

    template <typename LossFunctionType>
    template <typename ExampleIteratorType>
    predictors::DecisionTree SortingTreeLearner<LossFunctionType>::Train(ExampleIteratorType& exampleIterator)
    {
        predictors::DecisionTree tree;

        // create DenseRowDataset
        dataset::RowDataset<dataset::DoubleDataVector> denseDataset;
        while (exampleIterator.IsValid())
        {
            const auto& example = exampleIterator.Get();
            auto denseDataVector = std::make_unique<dataset::DoubleDataVector>(example.GetDataVector().ToArray(100));
            auto denseSupervisedExample = dataset::SupervisedExample<dataset::DoubleDataVector>(std::move(denseDataVector), example.GetLabel(), example.GetWeight());
            denseDataset.AddExample(std::move(denseSupervisedExample));
            exampleIterator.Next();
        }

        // TODO - replace the below with a real tree learning algo
        auto& root = tree.SplitRoot(predictors::DecisionTree::SplitRule(0, 0.0), -1.0, 1.0);
        root.GetNegativeChild().Split(predictors::DecisionTree::SplitRule(1, 1.0), -2.0, 2.0);
        root.GetPositiveChild().Split(predictors::DecisionTree::SplitRule(2, 2.0), -4.0, 4.0);

        return tree;
    }
}
