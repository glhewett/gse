/*
 *  gs_deserializer.h
 *
 *  Copyright (C) 2022
 *  Cisco Systems, Inc.
 *  All Rights Reserved
 *
 *  Description:
 *      The Game State Deserializer is an object that will decode game state
 *      data from a given data buffer.
 *
 *      These functions will utilize the provided DataBuffer object in order
 *      to deserialize various data types.  If an error occurs in reading from
 *      the data buffer, a DataBufferException may be thrown.  No attempt is
 *      made by the deserializer to restore the buffer's read length to what
 *      it was before the error is thrown.  Doing so consumes CPU cycles and
 *      likely of no benefit to the caller.
 *
 *      Each of the deserialization functions returns the number of octets
 *      read from the buffer.
 *
 *  Portability Issues:
 *      The C++ float and double types are assumed to be implemented following
 *      IEEE-754 specification.
 *
 *  License:
 *      BSD 2-Clause License
 *
 *      Copyright (c) 2022, Cisco Systems
 *      All rights reserved.
 *
 *      Redistribution and use in source and binary forms, with or without
 *      modification, are permitted provided that the following conditions are
 *      met:
 *
 *      1. Redistributions of source code must retain the above copyright
 *         notice, this list of conditions and the following disclaimer.
 *
 *      2. Redistributions in binary form must reproduce the above copyright
 *         notice, this list of conditions and the following disclaimer in the
 *         documentation and/or other materials provided with the distribution.
 *
 *      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 *      IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *      PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *      HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef GS_DESERIALIZER_H
#define GS_DESERIALIZER_H

#include <stdexcept>
#include "gs_types.h"
#include "data_buffer.h"

namespace gs
{

// DeserializerException exception definition
class DeserializerException : public std::runtime_error
{
    public:
        DeserializerException(const std::string &what_arg) :
            std::runtime_error(what_arg)
        {
        }
};

// Game State Deserializer object
class Deserializer
{
    public:
        Deserializer() = default;
        ~Deserializer() = default;

        // Read unsigned integer types
        std::size_t Read(std::unique_ptr<DataBuffer<>> &data_buffer,
                         Uint8 &value) const;
        std::size_t Read(std::unique_ptr<DataBuffer<>> &data_buffer,
                         Uint16 &value) const;
        std::size_t Read(std::unique_ptr<DataBuffer<>> &data_buffer,
                         Uint32 &value) const;
        std::size_t Read(std::unique_ptr<DataBuffer<>> &data_buffer,
                         Uint64 &value) const;

        // Read signed integer types
        std::size_t Read(std::unique_ptr<DataBuffer<>> &data_buffer,
                         Int8 &value) const;
        std::size_t Read(std::unique_ptr<DataBuffer<>> &data_buffer,
                         Int16 &value) const;
        std::size_t Read(std::unique_ptr<DataBuffer<>> &data_buffer,
                         Int32 &value) const;
        std::size_t Read(std::unique_ptr<DataBuffer<>> &data_buffer,
                         Int64 &value) const;

        // Read variable-width integer types
        std::size_t Read(std::unique_ptr<DataBuffer<>> &data_buffer,
                         VarUint &value) const;
        std::size_t Read(std::unique_ptr<DataBuffer<>> &data_buffer,
                         VarInt &value) const;

        // Read floating point types
        std::size_t Read(std::unique_ptr<DataBuffer<>> &data_buffer,
                         Float16 &value) const;
        std::size_t Read(std::unique_ptr<DataBuffer<>> &data_buffer,
                         Float32 &value) const;
        std::size_t Read(std::unique_ptr<DataBuffer<>> &data_buffer,
                         Float64 &value) const;

        // Read the Boolean type
        std::size_t Read(std::unique_ptr<DataBuffer<>> &data_buffer,
                         Boolean &value) const;

        // Read strings
        std::size_t Read(std::unique_ptr<DataBuffer<>> &data_buffer,
                         String &value) const;

        // Read a blob object
        std::size_t Read(std::unique_ptr<DataBuffer<>> &data_buffer,
                         Blob &value) const;
};

} // namespace gs

#endif // GS_DESERIALIZER_H
