// Copyright 2022 The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#ifndef MUMBLE_KEY_HPP
#define MUMBLE_KEY_HPP

#include "Macros.hpp"

#include <memory>
#include <string_view>

namespace mumble {
class MUMBLE_EXPORT Key {
public:
	class P;

	Key();
	Key(const Key &key);
	Key(Key &&key);
	Key(void *handle);
	Key(const std::string_view pem, const bool isPrivate, std::string_view password = {});
	virtual ~Key();

	virtual explicit operator bool() const;

	virtual Key &operator=(const Key &key);
	virtual Key &operator=(Key &&key);

	// XCR krzmbrzl: Should also provide operator!=
	// Davide: It's implicit. https://en.cppreference.com/w/cpp/language/operators
	virtual bool operator==(const Key &key) const;

	virtual void *handle() const;

	virtual bool isPrivate() const;

	// XCR krzmbrzl: Why return by value?
	// Davide: We store the certificate only through its OpenSSL handle.
	// The PEM string is generated and returned.
	virtual std::string pem() const;

private:
	std::unique_ptr< P > m_p;
};
} // namespace mumble

#endif
