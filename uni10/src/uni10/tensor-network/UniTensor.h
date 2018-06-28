    /****************************************************************************
 *  @file UniTensor.h
 *  @license
 *   Universal Tensor Network Library
 *   Copyright (c) 2013-2014
 *   National Taiwan University
 *   National Tsing-Hua University
 *
 *   This file is part of Uni10, the Universal Tensor Network Library.
 *
 *   Uni10 is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Uni10 is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with Uni10.  If not, see <http://www.gnu.org/licenses/>.
 *  @endlicense
 *  @brief Header file for UniTensor class
 *  @author Yun-Da Hsieh
 *  @date 2014-05-06
 *  @since 0.1.0
 *
 *****************************************************************************/
#ifndef UNITENSOR_H
#define UNITENSOR_H
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <string>
#include <assert.h>
#include <sstream>
#include <stdexcept>
#include <uni10/datatype.hpp>
#include <uni10/data-structure/uni10_struct.h>
#include <uni10/data-structure/Bond.h>
#include <uni10/data-structure/Block.h>
#include <uni10/tensor-network/Matrix.h>

/// @brief Uni10 - the Universal Tensor %Network Library
namespace uni10 {

    ///@class UniTensor
    ///@brief The UniTensor class defines the symmetric tensors
    ///
    /// A UniTensor consists of Bond's carrying quantum numbers Qnum's. The tensor elements are organized as
    /// quantum number blocks. The Qnum's on the Bonds defines the size of the Qnum blocks and the rank of
    /// UniTensor is defined by the number of Bond's.\par
    /// Each Bond carries a label. Labels are used to manipulate tensors, such as in permute, partialTrace and
    /// contraction. \par
    /// Operations on tensor elements is pefromed through  getBlock and putBlock functions to take out/put in
    /// block elements out as a Matrix.
    /// @see Qnum, Bond, Matrix
    /// @example egQ1.cpp
    /// @example egU1.cpp
    /// @example egU2.cpp
    /// @example egU3.cpp
    class Block;
    class Matrix;
    class UniTensor {

    public:
        friend void RtoC(UniTensor& UniT);

        /*******************  developping ************************/

        Real max() const;
        Real max(rflag tp) const;

        Real absMax() const;
        Real absMax(rflag tp) const;

        UniTensor& maxNorm();
        UniTensor& maxNorm(rflag tp);

        UniTensor& absMaxNorm();
        UniTensor& absMaxNorm(rflag tp);

        /// @brief Returns the \f$L^2\f$ norm of UniTensor elements
        ///
        /// @return \f$L^2\f$ norm
        Real norm() const;
        Real norm(rflag tp) const;
        Real norm(cflag tp) const;

        UniTensor& normalize();
        UniTensor& normalize(rflag tp);
        UniTensor& normalize(cflag tp);

        /// @brief Print the diagrammatic representation of  UniTensor
        ///
        /// Prints out the diagrammatic representation of UniTensor \c uT as (for example):
        /// @code
        ///**************** Demo ****************
        ///     ____________
        ///    |            |
        ///0___|3          3|___2
        ///    |            |
        ///1___|3          3|___3
        ///    |            |
        ///    |____________|
        ///
        /// @endcode
        void printDiagram()const;

        /// @brief Driver function for High-order SVD
        ///
        /// Performs High order SVD of UniTensor.
        /// @param[in] group_labels Ordered labels of the bonds
        /// @param[in] groups Number of external bonds in each mode
        /// @param[in] groupSize Number of modes
        /// @param[out] Ls Singular values on each direction
        ///
        /// @code
        /// ***** Example ******
        ///     ____________                     ______                      ____
        ///    |            |               0___|  U1  |__-1 ___     __-2___|    |___1
        ///8___|            |___0               |______|       _|___|_      | U2 |___2
        ///    |            |                                 |       |     |____|
        ///9___|            |___1                        __11_|       |
        ///    |            |                            __3__|       |
        ///11__|            |___2                             |   S   |
        ///    |            |                    ______       |       |      ____
        ///6___|            |___3            8__|      |__-4__|       |__-3_|    |___4
        ///    |            |                9__|  U4  |      |_______|     | U3 |___5
        ///5___|            |___4               |______|                    |____|___6
        ///    |            |
        ///    |____________|
        ///
        /// @endcode
        /// We want to decompose the tensor into a tensor of four modes and two bonds unchanged.
        ///
        /// @code
        /// Mode 1 {0,-1}
        /// Mode 2 {1,2,-2}
        /// Mode 3 {4,5,6,-3}
        /// Mode 4 {8,9,-4}
        /// Fixed {3,11}
        /// @endcode
        /// The input parameters are
        /// @code
        /// group_labels = { 0, 1, 2, 4, 5, 6, 8, 9, 3, 11 }
        /// groups={1,2,3,2}
        /// groupSize=4
        /// @endcode
        /// Returns unitaries \c U1, \c U2, \c U3, \c U4, and core tensor \c S
        std::vector<UniTensor> hosvd(int* group_labels, int* groups, size_t groupsSize, std::vector<Matrix>& Ls)const ;
        std::vector<UniTensor> hosvd(rflag tp, int* group_labels, int* groups, size_t groupsSize, std::vector<Matrix>& Ls)const ;
        std::vector<UniTensor> hosvd(cflag tp, int* group_labels, int* groups, size_t groupsSize, std::vector<Matrix>& Ls)const ;

        std::vector<UniTensor> hosvd(std::vector<int>& group_labels, std::vector<int>& groups, std::vector<Matrix>& Ls)const ;
        std::vector<UniTensor> hosvd(rflag tp, std::vector<int>& group_labels, std::vector<int>& groups, std::vector<Matrix>& Ls)const ;
        std::vector<UniTensor> hosvd(cflag tp, std::vector<int>& group_labels, std::vector<int>& groups, std::vector<Matrix>& Ls)const ;

        std::vector<UniTensor> hosvd(int* group_labels, int* groups, size_t groupsSize, std::vector<std::map<Qnum, Matrix> >& Ls, bool returnL)const ;

        std::vector<UniTensor> hosvd(rflag tp, int* group_labels, int* groups, size_t groupsSize, std::vector<std::map<Qnum, Matrix> >& Ls, bool returnL)const ;
        std::vector<UniTensor> hosvd(cflag tp, int* group_labels, int* groups, size_t groupsSize, std::vector<std::map<Qnum, Matrix> >& Ls, bool returnL)const ;

        std::vector<UniTensor> hosvd(std::vector<int>& group_labels, std::vector<int>& groups, std::vector<std::map<Qnum, Matrix> >& Ls, bool returnL)const ;

        std::vector<UniTensor> hosvd(rflag tp, std::vector<int>& group_labels, std::vector<int>& groups, std::vector<std::map<Qnum, Matrix> >& Ls, bool returnL)const ;
        std::vector<UniTensor> hosvd(cflag tp, std::vector<int>& group_labels, std::vector<int>& groups, std::vector<std::map<Qnum, Matrix> >& Ls, bool returnL)const ;

        UniTensor& cTranspose();
        UniTensor& cTranspose(cflag tp);

        /// @brief High-order SVD
        ///
        /// Performs High order SVD of UniTensor.
        /// @param modeNum Number of output modes
        /// @param fixedNum Number of bonds to remain unchanged
        /// @param Ls Singular values on each direction
        std::vector<UniTensor> hosvd(size_t modeNum, size_t fixedNum = 0)const;
        /// @overload
        std::vector<UniTensor> hosvd(size_t modeNum, size_t fixedNum, std::vector<std::map<Qnum, Matrix> >& Ls)const;
        /// @overload
        std::vector<UniTensor> hosvd(size_t modeNum, size_t fixedNum, std::vector<Matrix>& Ls)const;

        /**************** Real *****************************/
        std::vector<UniTensor> hosvd(rflag tp, size_t modeNum, size_t fixedNum = 0)const;

        std::vector<UniTensor> hosvd(rflag tp, size_t modeNum, size_t fixedNum, std::vector<std::map<Qnum, Matrix> >& Ls)const;
        std::vector<UniTensor> hosvd(rflag tp, size_t modeNum, size_t fixedNum, std::vector<Matrix>& Ls)const;

        std::vector<UniTensor> hosvd(cflag tp, size_t modeNum, size_t fixedNum = 0)const;

        std::vector<UniTensor> hosvd(cflag tp, size_t modeNum, size_t fixedNum, std::vector<std::map<Qnum, Matrix> >& Ls)const;
        std::vector<UniTensor> hosvd(cflag tp, size_t modeNum, size_t fixedNum, std::vector<Matrix>& Ls)const;

        /*********************  OPERATOR **************************/

        /// @brief Print out UniTensor
        ///
        /// Prints out a UniTensor \c uT as(for example):
        /// @code
        ///**************** Demo ****************
        ///     ____________
        ///    |            |
        ///0___|3          3|___2
        ///    |            |
        ///1___|3          3|___3
        ///    |            |
        ///    |____________|
        ///
        ///================BONDS===============
        ///IN : (U1 = 1, P = 0, 0)|1, (U1 = 0, P = 0, 0)|1, (U1 = -1, P = 0, 0)|1, Dim = 3
        ///IN : (U1 = 1, P = 0, 0)|1, (U1 = 0, P = 0, 0)|1, (U1 = -1, P = 0, 0)|1, Dim = 3
        ///OUT: (U1 = 1, P = 0, 0)|1, (U1 = 0, P = 0, 0)|1, (U1 = -1, P = 0, 0)|1, Dim = 3
        ///OUT: (U1 = 1, P = 0, 0)|1, (U1 = 0, P = 0, 0)|1, (U1 = -1, P = 0, 0)|1, Dim = 3
        ///
        ///===============BLOCKS===============
        ///--- (U1 = -2, P = 0, 0): 1 x 1 = 1
        ///
        ///0.840
        ///
        ///--- (U1 = -1, P = 0, 0): 2 x 2 = 4
        ///
        ///0.394  0.783
        ///
        ///0.798  0.912
        ///
        ///--- (U1 = 0, P = 0, 0): 3 x 3 = 9
        ///
        ///0.198  0.335  0.768
        ///
        ///0.278  0.554  0.477
        ///
        ///0.629  0.365  0.513
        ///
        ///--- (U1 = 1, P = 0, 0): 2 x 2 = 4
        ///
        ///0.952  0.916
        ///
        ///0.636  0.717
        ///
        ///--- (U1 = 2, P = 0, 0): 1 x 1 = 1
        ///
        ///0.142
        ///
        ///Total elemNum: 19
        ///***************** END ****************
        /// @endcode
        ///  In the above example, \c uT has four bonds with default labels [0, 1, 2, 3]. The bonds 0 and 1 are
        /// incoming bonds, and  2, 3 are out-going bonds. Each bond has three states
        /// corresponding to three U1 quantum number [-1, 0, 1]. The block elements of the
        /// tensor are als shown. There are five blocks of various <tt>U1= [-2, -1, 0, 1, 2]</tt> and
        /// various sizes. The total element number is 19.
        friend std::ostream& operator<< (std::ostream& os, const UniTensor& UniT);

        /// @brief Multiply UniTensor by a scalar and assign
        ///
        /// Performs element-wise multiplication with a scalar \c a.
        /// @param a A scalar
        UniTensor& operator*= (Real a);
        /// @brief Multiply UniTensor by a scalar and assign
        ///
        /// Performs element-wise multiplication with a scalar \c a.
        /// @param a A scalar
        UniTensor& operator*= (Complex a);

        /// @brief   Contract UniTensor with a second tensor and assign
        ///
        /// Performs tensor contraction with another UniTensor \c Tb. It contracts out the bonds of the same
        /// labels in the UniTensor and \c Tb
        /// @param Tb A second UniTensor
        UniTensor& operator*= (const UniTensor& Tb);

        /// @brief Muliplication
        ///
        /// Performs element-wise multiplication with a scalar \c a
        /// @param a Scalar to be multiplied to UniTensor
        friend UniTensor operator*(const UniTensor& Ta, const Complex& a);
        /// @overload
        friend UniTensor operator*(const Complex& a, const UniTensor& Ta);
        /// @brief Muliplication
        ///
        /// Performs element-wise multiplication with a scalar \c a
        /// @param a Scalar to be multiplied to UniTensor
        friend UniTensor operator*(const UniTensor& Ta, Real a);
        /// @overload
        friend UniTensor operator*(Real a, const UniTensor& Ta);

        /// @brief Tensor contraction
        ///
        /// Performs tensor contraction, <tt> Ta * Tb </t>. It contracts  the bonds of the same labels in \c Ta
        /// and \c Tb by making copies and then call function \ref{contract}.
        friend UniTensor operator*(const UniTensor& Ta, const UniTensor& Tb);

        /// @brief Copy content
        ///
        /// Assigns new content to the UniTensor from \c UniT, replacing the original contents
        /// @param UniT Tensor to be copied
        ///
        UniTensor& operator=(const UniTensor& UniT);

        /// @brief   Perform  element-wise addition and assign
        ///
        /// Performs element-wise addition. The tensor \c Tb to be added must be \ref{similar} to  UniTensor.
        /// @see UniTensor::similar()
        /// @param Tb A second UniTensor
        UniTensor& operator+= (const UniTensor& Tb);

        /// @brief Perform  element-wise addition
        /// Performs element-wise addition.
        /// @param Ta,Tb Tensors to be added
        friend UniTensor operator+ (const UniTensor& Ta, const UniTensor& Tb);

        /*********************  NO TYPE **************************/

        ///
        /// @brief Default Constructor
        ///
        UniTensor();

        /// @brief Create a rank-0 UniTensor with value \c val
        ///
        /// @param val Value of the scalar
        UniTensor(const std::vector<Bond>& _bonds, const std::string& _name = "");
        UniTensor(const std::string tp, const std::vector<Bond>& _bonds, const std::string& _name = "");

        /// @brief Create a UniTensor from a list of Bond's
        /// @param _bonds List of bonds
        /// @param _name Name of the tensor, defaults to ""
        UniTensor(const std::vector<Bond>& _bonds, std::vector<int>& labels, const std::string& _name = "");

        /// @brief Create a UniTensor from a list of Bond's and assign labels
        /// @param _bonds List of bonds
        /// @param labels Labels for \c _bonds
        /// @param _name Name of the tensor, defaults to ""
        UniTensor(const std::vector<Bond>& _bonds, int* labels, const std::string& _name = "");

        /// @brief Copy constructor
        UniTensor(const UniTensor& UniT);

        /// @brief Create a UniTensor from a file
        ///
        /// @param fname Filename to be read in
        UniTensor(const std::string& fname);

#ifdef HDF5
        /// @brief Create a UniTensor from a HDF5 file
        ///
        /// @param fname Filename to be read in
        UniTensor(const std::string& fname, const bool hdf5);
#endif
        /// @brief Create a UniTensor from a Block
        UniTensor(const Block& UniT);

        /// @brief Destructor
        ///
        /// Destroys the UniTensor and freeing all allocated memory
        ~UniTensor();

        /// @brief Assign raw elements
        ///
        /// Assigns raw elements in \c blk to UniTensor.
        ///
        /// This function will reorganize the raw elements into the block-diagonal form.
        /// @param blk  Block of raw elements
        void setRawElem(const Block& blk);

        /// @brief Assign elements to a block
        ///
        /// Assigns elements of the  matrix \c mat to the  block of quantum number \c qnum, replacing the origin
        /// elements. \par
        /// If \c mat is diagonal,  all the off-diagonal elements are set to zero.
        /// @param mat The matrix elements to be assigned
        void putBlock(const Block& mat, bool force=false);

        /// @brief Assign elements to a block
        ///
        /// Assigns elements of the  matrix \c mat to the  Qnum(0) block, for non-symmetry tensors.
        ///
        /// If \c mat is diagonal,  all the off-diagonal elements are set to zero.
        /// @param qnum quantum number of the block
        /// @param mat The matrix elements to be assigned
        void putBlock(const Qnum& qnum, const Block& mat, bool force=false);

        int typeID()const;

        ///
        void setLabel(const int newLabel, const size_t idx);
        /// @brief Assign labels to bonds in UniTensor
        ///
        /// Assigns the labels \c newLabels to each bond of  UniTensor, replacing the origin labels on the bonds.
        /// @param newLabels array of labels
        void setLabel(const std::vector<int>& newLabels);

        /// @overload
        void setLabel(int* newLabels);

        /// @brief Access labels
        ///
        /// Returns the labels of the bonds in UniTensor
        ///
        /// @return List of labels
        std::vector<int> label()const;

        /// @brief Access label
        ///
        /// Access the label of Bond \c idx
        /// @param idx Bond index
        /// @return Label of Bond \c idx
        int label(size_t idx)const;

        /// @brief Access name
        ///
        /// Return the name of the UniTensor.
        std::string getName() const;

        /// @brief Assign name
        ///
        /// Assigns name to the UniTensor.
        /// @param name Name to be assigned
        void setName(const std::string& _name);

        /// @brief Access the number of bonds
        ///
        /// @return Number of bonds
        size_t bondNum()const;

        /// @brief Access the number of incoming bonds
        ///
        /// @return Number of incoming bonds
        size_t inBondNum()const;

        /// @brief Access bonds
        ///
        /// Returns the bonds in UniTensor
        /// @return List of bonds
        std::vector<Bond> bond()const;

        /// @brief Access bond
        ///
        /// Returns the bond at the position \c idx
        /// @param idx Position of the bond being retrieved
        /// @return A bond
        Bond bond(size_t idx)const;

        /// @brief Access the number of elements
        ///
        /// Returns the number of total elements of the blocks.
        /// @return  Number of elements
        size_t elemNum()const;

        /// @brief Access the number of blocks
        ///
        /// Returns the number of blocks
        /// @return The number of blocks
        size_t blockNum()const;

        /// @brief Access block quantum numbers
        ///
        /// Returns the quantum numbers for all blocks in UniTensor.
        /// The return array of quantum numbers is in the ascending order defined in Qnum.
        /// @return Array of Qnum's
        std::vector<Qnum> blockQnum()const;

        /// @brief Access block quantum number
        ///
        /// Returns the quantum number for block \c idx in UniTensor.
        /// Blocks are orderd in the ascending order of Qnum
        /// @param idx Block index
        /// @return Quantum number of block \c idx
        Qnum blockQnum(size_t idx)const;

        /// @brief Access block elements
        ///
        /// Returns the tensor element blocks of Qnums as
        ///  a const map from a composite Qnum to a corresponding element block
        ///
        /// @return   Map from Qnum to Block
        const std::map<Qnum, Block>& const_getBlocks()const;

        /// @brief Get elements in a block
        ///
        /// Returns elements of Qnum(0) Block.
        /// @return The Qnum(0) Block
        const Block& const_getBlock()const;

        /// @brief Get elements in a block
        ///
        /// Returns elements of \c qnum block.
        /// @return The \c qnum  Block
        const Block& const_getBlock(const Qnum& qnum)const;

        /// @brief Access block elements
        ///
        /// Returns the tensor element blocks of Qnums as
        ///  a map from a composite Qnum to a corresponding element block as Matrix
        ///
        /// @return   Map from Qnum to Matrix
        std::map<Qnum, Matrix> getBlocks()const;

        /// @brief Get elements in a block
        ///
        /// Returns a Matrix of Qnum(0) block elements. If the \c diag flag is set,
        /// only  diagonal elements in the block will be copied to a diagonal Matrix.
        /// @param diag Set \c true to save only the diagonal elements
        /// @return A Matrix of Qnum(0) block
        Matrix getBlock(bool diag = false)const;

        /// @brief Get elements in a block
        ///
        /// Returns the block elements of a quantum number \c qnum as a Matrix. If the \c diag flag is set,
        /// only  diagonal elements in the block will be copied to a diagonal Matrix.
        /// @param diag Set \c true to save only the diagonal elements
        /// @return A Matrix of \c qnum block
        Matrix getBlock(const Qnum& qnum, bool diag = false)const;

        /// @brief Assign elements
        ///
        /// Set all  elements to zero.
        void set_zero();

        /// @brief Assign elements
        ///
        /// Set all  elements in the block with quantum number \c qnum to zero.
        /// @param qnum Block quantum number
        void set_zero(const Qnum& qnum);

        /// @brief Assign elements
        ///
        /// Set diagonal elements of blocks to one.
        void identity();

        /// @brief Assign elements
        ///
        /// Set diagonal elements of block with \c qnum to one.
        /// @param qnum Block quantum number
        void identity(const Qnum& qnum);

        /// @brief Assign elements
        ///
        /// Assigns random numbers in [0, 1) to the elements.
        void randomize();

        /// @brief Assign elements
        ///
        /// Assigns randomly generated orthogonal bases to the elements of UniTensor.
        ///
        ///  \c Nr = row() and \c Nc = col().
        ///
        /// If the <tt> Nr < Nc </tt>, randomly generates \c Nr orthogonal basis row vectors of dimension \c Nc.
        /// If the <tt> Nr > Nc </tt>, randomly generates \c Nc orthogonal basis column vectors of
        /// dimension \c Nr.
        void orthoRand();
        /// @brief Assign elements
        ///
        /// Assigns randomly generated orthogonal bases to the elements of \c qnum block.
        /// @param qnum Block quantum number
        void orthoRand(const Qnum& qnum);

        /// @brief Save UniTensor to file
        ///
        /// Saves UniTensor to a file named \c fname.
        /// @param fname filename
        void save(const std::string& fname) const;

#ifdef HDF5
        /// @brief Save UniTensor to HDF5 file
        ///
        /// Saves UniTensor to a HDF5 file named \c fname.
        /// @param fname filename
        void h5save(const std::string& fname);
#endif
        /// @brief Transpose  block elements
        ///
        /// Transpose each quantum number block. The bonds are changed from incoming to outcoming and vice versa
        /// without changing the quantum numbers on the bonds.
        UniTensor& transpose();

        /// @brief Permute the order of bonds
        ///
        /// Permutes the order of bonds to the order according to \c newLabels with \c inBondNum incoming bonds.
        /// @param newLabels list of new labels
        /// @param inBondNum Number of incoming bonds after permutation
        UniTensor& permute(const std::vector<int>& newLabels, int inBondNum);
        /// @overload
        UniTensor& permute(int* newLabels, int inBondNum);
        /// @brief Permute the order of bonds
        ///
        /// Rearranges the number of incoming and outgoing bonds without changing the order of the bonds.
        /// It assigns the first \c inBondNum bonds as incoming bonds and leaving the remaining bonds as
        /// outgoing bonds
        /// @param inBondNum Number of incoming bonds after permutation
        UniTensor& permute(int inBondNum);

        /// @brief Perform contraction of UniTensor
        ///
        /// Performs tensor contraction of \c Ta and \c Tb. It contracts out the bonds of the same labels
        /// in \c Ta and \c Tb.

        /// @note  In contrast to \ref{ operator*} as in <tt>Ta * Tb </tt>,  this function performs
        /// contraction without copying \c Ta and \c Tb. Thus it uses less memory. When the flag \c fast is set
        /// \c true, the two tensors \c Ta and \c Tb are contracted without permuting back to origin labels.
        /// @return Ta,Tb Tensors to be contracted.
        /// @param fast A flag to set if permuted back to origin labels.  If \c true, two tensor are not
        /// permuted back. Defaults to \c false
        friend UniTensor contract(UniTensor& Ta, UniTensor& Tb, bool fast);

        /// @brief Tensor product of two tensors
        ///
        /// Performs tensor product of \c Ta and \c Tb.
        /// @param Ta,Tb Tensors to perform tensor product.
        friend UniTensor otimes(const UniTensor& Ta, const UniTensor& Tb);


        /// @brief Combine bonds
        ///
        /// Combines  bonds with labels in \c combined_labels.
        /// The resulting bond has the same label and bondType as the bond with the first label.
        /// @param combined_labels labels to be combined
        UniTensor& combineBond(const std::vector<int>& combined_labels);

        /// @brief Print out raw elements
        /// Prints out raw elements of UniTensor as the following example,
        ///@code
        ///         2,0    1,0    0,0    1,0    0,0   -1,0    0,0   -1,0   -2,0
        ///        -----------------------------------------------------------------
        ///        |
        ///     2,0|  0.142  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
        ///        |
        ///     1,0|  0.000  0.952  0.000  0.916  0.000  0.000  0.000  0.000  0.000
        ///        |
        ///     0,0|  0.000  0.000  0.198  0.000  0.335  0.000  0.768  0.000  0.000
        ///        |
        ///     1,0|  0.000  0.636  0.000  0.717  0.000  0.000  0.000  0.000  0.000
        ///        |
        ///     0,0|  0.000  0.000  0.278  0.000  0.554  0.000  0.477  0.000  0.000
        ///        |
        ///    -1,0|  0.000  0.000  0.000  0.000  0.000  0.394  0.000  0.783  0.000
        ///        |
        ///     0,0|  0.000  0.000  0.629  0.000  0.365  0.000  0.513  0.000  0.000
        ///        |
        ///    -1,0|  0.000  0.000  0.000  0.000  0.000  0.798  0.000  0.912  0.000
        ///        |
        ///    -2,0|  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.840
        ///@endcode
        ///In the above example,  UniTensor has two incoming  and two outgoing bonds, with each bond having
        /// states with Qnum's <tt>[q(1), q(0), q(-1)]</tt>. The raw elements form a 9 by 9 Matrix.
        /// The first row shows the Qnum's, \c U1 and \c parity, in the columns below and the first column
        /// shows the quantum numbers of the rows on the right.
        std::string printRawElem(bool print=true)const;

        /// @brief Print out  memory usage of the existing UniTensor's
        ///
        /// Prints out the memory usage as (for example):
        ///
        ///
        ///     Existing Tensors: 30
        ///     Allocated Elem: 2240
        ///     Max Allocated Elem: 4295
        ///     Max Allocated Elem for a Tensor: 924
        ///
        /// In the above example, currently there are 30 tensors and total number of existing elements is 2240.
        /// The maximum element number for now is 4295 and the maximum element number of a tensor is 924.
        static std::string profile(bool print = true);
        std::vector<_Swap> exSwap(const UniTensor& Tb)const;
        void addGate(const std::vector<_Swap>& swaps);

        /// @brief Trace
        /// Traces all bonds and returns the trace value.
        /// @return Trace of UniTensor
        Complex trace()const;

        /// @brief Partial trace
        ///
        /// Traces out  two bond with labels \c la and \c lb.
        /// @param la,lb Labels of the bonds to be traced out
        UniTensor& partialTrace(int la, int lb);


        /// @brief Access raw elements.
        ///
        /// Returns the elements of UniTensor in the non-block-diagonal form (raw elements) as a Matrix.
        /// The row(or column) bases of the elements are defined by the incoming bonds(or outgoing) bonds.
        ///
        /// @return Matrix of raw elements.
        Matrix getRawElem()const;

        /// @brief Assign bonds
        ///
        /// Reconstructs the tensor with given bonds, replacing the original ones and clear the content of
        /// UniTensor
        /// @param _bond array of bonds
        UniTensor& assign(const std::vector<Bond>& _bond);

        bool CelemIsNULL();
        bool RelemIsNULL();

        /// @brief Test if two tensors are similar
        ///
        /// Two UniTensor's are  similar if the bonds of two tensors are the same.
        /// @param Tb A second UniTensor
        /// @return \c True if  UniTensor is similar to \c Tb, \c false otherwise.
        bool similar(const UniTensor& Tb)const;

        /// @brief Test if the elements of two tensors are the same
        ///
        /// Performs the element-wise comparison of UniTensor and \c Tb. Returns \c true if all the elements are
        ///the same.
        /// @param uT  UniTensor to be compared
        /// @return \c True if the elements of  UniTensor is the same as in \c Tb, \c false otherwise.
        bool elemCmp(const UniTensor& UniT)const;

        /// @brief Reset status to no elements
        void clear();

        /*********************  REAL **********************/

        UniTensor(Real val);
        UniTensor(rflag tp, const std::vector<Bond>& _bonds, const std::string& _name = "");
        UniTensor(rflag tp, const std::vector<Bond>& _bonds, std::vector<int>& labels, const std::string& _name = "");
        UniTensor(rflag tp, const std::vector<Bond>& _bonds, int* labels, const std::string& _name = "");

        /// @brief Assign raw elements
        ///
        /// Assigns raw elements in \c rawElem to Real or None type UniTensor.
        /// The raw elements are organized in the basis given in the bonds.
        ///
        /// This function will reorganize the raw elements into the block-diagonal form.
        /// @param rawElem array of raw elements
        void setRawElem(const std::vector<Real>& rawElem);
        /// @overload
        void setRawElem(const Real* rawElem);

        void setRawElem(rflag tp, const Block& blk);

        /// @brief Assign elements to a block
        ///
        /// Assigns elements of the  matrix \c mat to the  block of quantum number \c qnum, replacing the origin
        /// elements. \par
        /// If \c mat is diagonal,  all the off-diagonal elements are set to zero.
        /// @param mat The matrix elements to be assigned
        void putBlock(rflag tp, const Block& mat, bool force=false);

        void putBlock(rflag tp, const Qnum& qnum, const Block& mat, bool force=false);

        void setElem(const Real* elem, bool _ongpu = false);

        /// @overload
        void setElem(const std::vector<Real>& elem, bool _ongpu = false);
        void setElemR(double* in_array, int elem_num);

        std::map<Qnum, Matrix> getBlocks(rflag tp)const;

        Matrix getBlock(rflag tp, bool diag = false)const;

        Matrix getBlock(rflag tp, const Qnum& qnum, bool diag = false)const;

        void set_zero(rflag tp);
        void set_zero(rflag tp, const Qnum& qnum);
        void identity(rflag tp);
        void identity(rflag tp, const Qnum& qnum);
        void randomize(rflag tp);

        void orthoRand(rflag tp);
        void orthoRand(rflag tp, const Qnum& qnum);

        UniTensor& transpose(rflag tp);

        UniTensor& permute(rflag tp, const std::vector<int>& newLabels, int inBondNum);

        UniTensor& permute(rflag tp, int* newLabels, int inBondNum);

        UniTensor& permute(rflag tp, int inBondNum);

        friend UniTensor contract(rflag tp, UniTensor& Ta, UniTensor& Tb, bool fast);

        friend UniTensor otimes(rflag tp, const UniTensor& Ta, const UniTensor& Tb);

        UniTensor& combineBond(rflag tp, const std::vector<int>& combined_labels);
        void addGate(rflag tp, const std::vector<_Swap>& swaps);

        Matrix getRawElem(rflag tp)const;

        Real trace(rflag tp)const;
        UniTensor& partialTrace(rflag tp, int la, int lb);
        UniTensor& assign(rflag tp, const std::vector<Bond>& _bond);

        /*********************  COMPLEX **********************/

        UniTensor(Complex val);
        UniTensor(cflag tp, const std::vector<Bond>& _bonds, const std::string& _name = "");
        UniTensor(cflag tp, const std::vector<Bond>& _bonds, std::vector<int>& labels, const std::string& _name = "");
        UniTensor(cflag tp, const std::vector<Bond>& _bonds, int* labels, const std::string& _name = "");

        /// @overload
        void setRawElem(const std::vector< Complex >& rawElem);

        /// @overload
        void setRawElem(const Complex* rawElem);

        /// @overload
        void setRawElem(cflag tp, const Block& blk);

        void putBlock(cflag tp, const Block& mat, bool force=false);

        void putBlock(cflag tp, const Qnum& qnum, const Block& mat, bool force=false);

        void setElem(const Complex* c_elem, bool _ongpu = false);

        void setElem(const std::vector< Complex >& c_elem, bool _ongpu = false);
        void setElemC(Complex* in_array, int elem_num);

        std::map<Qnum, Matrix> getBlocks(cflag tp)const;

        Matrix getBlock(cflag tp, bool diag = false)const;

        Matrix getBlock(cflag tp, const Qnum& qnum, bool diag = false)const;

        void set_zero(cflag tp);

        void set_zero(cflag tp, const Qnum& qnum);

        void identity(cflag tp);

        void identity(cflag tp, const Qnum& qnum);

        void randomize(cflag tp);

        void orthoRand(cflag tp);

        void orthoRand(cflag tp, const Qnum& qnum);

        UniTensor& transpose(cflag tp);

        UniTensor& permute(cflag tp, const std::vector<int>& newLabels, int inBondNum);

        UniTensor& permute(cflag tp, int* newLabels, int inBondNum);

        UniTensor& permute(cflag tp, int inBondNum);

        friend UniTensor contract(cflag tp, UniTensor& Ta, UniTensor& Tb, bool fast);

        friend UniTensor otimes(cflag tp, const UniTensor& Ta, const UniTensor& Tb);

        UniTensor& combineBond(cflag tp, const std::vector<int>& combined_labels);
        void addGate(cflag tp, const std::vector<_Swap>& swaps);

        Matrix getRawElem(cflag tp)const;
        Complex trace(cflag tp)const;
        UniTensor& partialTrace(cflag tp, int la, int lb);
        UniTensor& assign(cflag tp, const std::vector<Bond>& _bond);

        /*************************************/

        /// @brief Access single element
        ///
        /// Returns the element at position specified by the indices \c idxs.
        /// The size of the array \c idxs is equal to the total number of bonds
        /// @param idxs  An array of indices
        /// @return The element at indices \c idxs.
        Real at(size_t idx)const;
        /// @overload
        Real at(const std::vector<int>& idxs)const;
        /// @overload
        Real at(const std::vector<size_t>& idxs)const;
        Real at(rflag tp, size_t idx)const;
        Real at(rflag tp, const std::vector<int>& idxs)const;
        Real at(rflag tp, const std::vector<size_t>& idxs)const;
        Complex at(cflag tp, size_t idx)const;
        Complex at(cflag tp, const std::vector<int>& idxs)const;
        Complex at(cflag tp, const std::vector<size_t>& idxs)const;

        /// @brief Access element array
        ///
        Real* getElem();
        Real* getElem(rflag tp);
        void exportElemR(double *out_array, int elem_num = -1);
        Complex* getElem(cflag tp);
        void exportElemC(Complex *out_array, int elem_num = -1);

        /// @brief Access individual element
        ///
        /// Returns the Real element at linear position \c idx.
        /// The first bond’s dimension is the most significant
        /// dimension.
        ///
        /// @param  idx linear position of element
        /// @return Element of Real type at index \c idx.
        Real operator[](size_t idx) const;
        /// @brief Access individual element
        ///
        /// Returns the Complex element at linear position \c idx.
        /// The first bond’s dimension is the most significant dimension.
        ///
        /// @param  idx linear position of element
        /// @return Element of Complex type at index \c idx.

        Complex operator()(size_t idx) const;

        /*************************************/

        friend class Node;
        friend class Network;

    private:

        rflag r_flag;
        cflag c_flag;
        std::string name;
        Real *elem;       //Array of elements
        Complex* c_elem;       //Array of elements
        int status; //Check initialization, 1 initialized, 3 initialized with label, 5 initialized with elements
        std::vector<Bond> bonds;
        std::map<Qnum, Block> blocks;
        std::vector<int>labels;
        void packMeta();
        int RBondNum;   //Row bond number
        int RQdim;
        int CQdim;
        size_t m_elemNum;
        std::map<int, Block*> RQidx2Blk;    //Qidx to the Block
        std::map<int, size_t> QidxEnc;
        std::map<int, size_t> RQidx2Off;    //the row offset starts from the block origin of a qnum
        std::map<int, size_t> CQidx2Off;    //the col offset starts from the block origin of a qnum
        std::map<int, size_t> RQidx2Dim;
        std::map<int, size_t> CQidx2Dim;
        bool ongpu;
        static int COUNTER;
        static int64_t ELEMNUM;
        static size_t MAXELEMNUM;
        static size_t MAXELEMTEN;   //Max number of element of a tensor

        //Private Functions
        /*********************  NO TYPE **************************/
        void initUniT(int typeID);
        std::vector<UniTensor> _hosvd(size_t modeNum, size_t fixedNum, std::vector<std::map<Qnum, Matrix> >& Ls, bool returnL)const;
        void TelemFree();
        /*********************  REAL **********************/
        void initUniT(rflag tp = RTYPE);
        size_t grouping(rflag tp = RTYPE);
        void initBlocks(rflag tp = RTYPE);
        void TelemAlloc(rflag tp = RTYPE);
        void TelemBzero(rflag tp = RTYPE);
        void exportElem(rflag tp, double *out_array, int elem_num);
        /*********************  COMPLEX **********************/
        void initUniT(cflag tp);
        size_t grouping(cflag tp);
        void initBlocks(cflag tp);
        void TelemAlloc(cflag tp);
        void TelemBzero(cflag tp);
        void exportElem(cflag tp, Complex *out_array, int elem_num);
        /*****************************************************/

        static const int HAVEBOND = 1;        /**< A flag for initialization */
        static const int HAVEELEM = 2;        /**< A flag for having element assigned */
    };
    void RtoC(UniTensor& UniT);
    UniTensor contract(UniTensor& Ta, UniTensor& Tb, bool fast = false);
    UniTensor contract(rflag tp, UniTensor& Ta, UniTensor& Tb, bool fast = false);
    UniTensor contract(cflag tp, UniTensor& Ta, UniTensor& Tb, bool fast = false);
    UniTensor otimes(const UniTensor& Ta, const UniTensor& Tb);
    UniTensor otimes(rflag tp, const UniTensor& Ta, const UniTensor& Tb);
    UniTensor otimes(cflag tp, const UniTensor& Ta, const UniTensor& Tb);
};  /* namespace uni10 */
#endif /* UNITENSOR_H */
