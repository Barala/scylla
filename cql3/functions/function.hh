/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Copyright 2014 Cloudius Systems
 *
 * Modified by Cloudius Systems
 */

#pragma once

#include "function_name.hh"
#include "types.hh"
#include <vector>
#include <experimental/optional>

namespace cql3 {
namespace functions {

class function {
public:
    using opt_bytes = std::experimental::optional<bytes>;
    virtual ~function() {}
    virtual const function_name& name() const = 0;
    virtual const std::vector<data_type>& arg_types() const = 0;
    virtual data_type return_type() const = 0;

    /**
     * Checks whether the function is a pure function (as in doesn't depend on, nor produce side effects) or not.
     *
     * @return <code>true</code> if the function is a pure function, <code>false</code> otherwise.
     */
    virtual bool is_pure() = 0;

    /**
     * Checks whether the function is a native/hard coded one or not.
     *
     * @return <code>true</code> if the function is a native/hard coded one, <code>false</code> otherwise.
     */
    virtual bool is_native() = 0;

    /**
     * Checks whether the function is an aggregate function or not.
     *
     * @return <code>true</code> if the function is an aggregate function, <code>false</code> otherwise.
     */
    virtual bool is_aggregate() = 0;

    virtual void print(std::ostream& os) const = 0;
    virtual bool uses_function(const sstring& ks_name, const sstring& function_name) = 0;
    virtual bool has_reference_to(function& f) = 0;
    friend class function_call;
    friend std::ostream& operator<<(std::ostream& os, const function& f);
};

inline
std::ostream&
operator<<(std::ostream& os, const function& f) {
    f.print(os);
    return os;
}

}
}
