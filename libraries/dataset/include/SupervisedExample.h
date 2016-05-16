////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     SupervisedExample.h (dataset)
//  Authors:  Ofer Dekel
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "IDataVector.h"

// stl
#include <cstdint>
#include <memory>
#include <algorithm> // for std::swap

namespace dataset
{
    /// <summary> A supervised example. </summary>
    template<typename DataVectorType>
    class SupervisedExample 
    {
    public:

        /// <summary> Default constructor. </summary>
        SupervisedExample() = default;

        /// <summary> Copy constructor </summary>
        ///
        /// <param name="other"> The other. </param>
        SupervisedExample(const SupervisedExample<DataVectorType>& other) = delete; // { throw std::exception(); }//= delete;

        /// <summary> Default move constructor. </summary>
        ///
        /// <param name="other"> [in,out] The other. </param>
        SupervisedExample(SupervisedExample<DataVectorType>&& other) = default;
        
        /// <summary> Constructs a supervised example. </summary>
        ///
        /// <param name="dataVector"> The data vector. </param>
        /// <param name="label"> The label. </param>
        /// <param name="weight"> The weight. </param>
        SupervisedExample(std::shared_ptr<const DataVectorType> dataVector, double label, double weight = 1.0);

        /// <summary> Assignment operator. </summary>
        ///
        /// <param name="other"> The other. </param>
        ///
        /// <returns> A reference to this SupervisedExample. </returns>
        SupervisedExample& operator=(const SupervisedExample<DataVectorType>& other) = delete;

        /// <summary> Move assignment operator. </summary>
        ///
        /// <param name="other"> [in,out] The other. </param>
        ///
        /// <returns> A reference to this SupervisedExample. </returns>
        SupervisedExample& operator=(SupervisedExample<DataVectorType>&& other) = default;

        /// <summary> Returns a shallow copy of the supervised example. A shallow copy has its own weight and label, but shares the data vector. </summary>
        ///
        /// <returns> A SupervisedExample. </returns>
        SupervisedExample<DataVectorType> ShallowCopy() const;

        /// <summary> Returns a deep copy of the supervised example. </summary>
        ///
        /// <returns> A SupervisedExample. </returns>
        SupervisedExample<DataVectorType> DeepCopy() const;

        /// <summary> Gets the data vector. </summary>
        ///
        /// <returns> The data vector. </returns>
        const DataVectorType& GetDataVector() const;

        /// <summary> Gets the weight. </summary>
        ///
        /// <returns> The weight. </returns>
        double GetWeight() const;

        /// <summary> Gets the label. </summary>
        ///
        /// <returns> The label. </returns>
        double GetLabel() const;

        /// <summary> Prints the datavector to an output stream. </summary>
        ///
        /// <param name="os"> [in,out] Stream to write data to. </param>
        void Print(std::ostream& os) const;

    private:
        std::shared_ptr<const DataVectorType> _dataVector;
        double _label;
        double _weight;
    };

    /// <summary> Stream insertion operator. </summary>
    ///
    /// <param name="ostream"> [in,out] Stream to write data to. </param>
    /// <param name="example"> The example. </param>
    ///
    /// <returns> The shifted ostream. </returns>
    template<typename DataVectorType>
    std::ostream& operator<<(std::ostream& ostream, const SupervisedExample<DataVectorType>& example);

    typedef SupervisedExample<IDataVector> GenericSupervisedExample;
}

#include "../tcc/SupervisedExample.tcc"
