/* This file is part of the wvWare 2 project
   Copyright (C) 2001-2003 Werner Trobin <trobin@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/

#ifndef OLESTREAM_H
#define OLESTREAM_H

#include "olestorage.h"
#include "global.h"  // U8,... typedefs
#include <stack>
#include <stdio.h> //seek type

#define GSeekType int
#define G_SEEK_SET SEEK_SET
#define G_SEEK_CUR SEEK_CUR
#define G_SEEK_END SEEK_END

namespace wvWare {

class OLEStream
{
public:
    /**
     * Create an OLE stream
     */
    OLEStream( OLEStorage *storage );
    virtual ~OLEStream();

    /**
     * Is this still a valid stream?
     */
    virtual bool isValid() const = 0;

    /**
     * works like plain fseek
     */
    virtual bool seek( int offset, GSeekType whence = G_SEEK_SET ) = 0;
    /**
     * works like plain ftell
     */
    virtual int tell() const = 0;
    /**
     * The size of the stream
     */
    virtual size_t size() const = 0;

    /**
     * Push the current offset on the stack
     */
    void push();
    /**
     * Pop the topmost position (false if the stack was empty)
     */
    bool pop();

private:
    /**
     * we don't want to allow copying and assigning streams
     */
    OLEStream( const OLEStream& rhs );
    /**
     * we don't want to allow copying and assigning streams
     */
    OLEStream& operator=( const OLEStream& rhs );

    std::stack<int> m_positions;
    /**
     *  for bookkeeping :}
     */
    OLEStorage *m_storage;
};

class WV2_DLLEXPORT OLEStreamReader : public OLEStream
{
	public:
        OLEStreamReader(OLEStorage* storage);
		virtual ~OLEStreamReader();
		virtual bool isValid() const = 0;
        virtual bool seek( int offset, GSeekType whence = G_SEEK_SET ) = 0;
		virtual int tell() const = 0;
		virtual size_t size() const = 0;
		virtual U8 readU8() = 0;
		virtual S8 readS8() = 0;
		virtual U16 readU16() = 0;
		virtual S16 readS16() = 0;
		virtual U32 readU32() = 0;
		virtual S32 readS32() = 0;
		virtual bool read( U8 *buffer, size_t length ) = 0;
};


/**
 * OLEImageReader provides bounds-checked access to a stream.
 * Objects of this class are used to safely provide image data to
 * the consumer.
 * It doesn't actually own an OLE stream, it just wraps the access
 * to the real data stream. In that wrapper code it also performs
 * the bounds checking.
 * Note that this stream class, unlike the other two classes, doesn't
 * fix the endianness of the data!
 */
class OLEImageReader
{
public:
    /**
    * Constructs a limited reader which is only allowed to read the passed
    * OLEStreamReader from start up to, but not including, limit.
    */
    OLEImageReader( OLEStreamReader& reader, unsigned int start, unsigned int limit );
    OLEImageReader( const OLEImageReader& rhs );

    ~OLEImageReader();

    /**
    * Is this still a valid stream?
    */
    bool isValid() const;

    /**
    * Works like plain fseek, with the limitation of the defined region.
    */
    bool seek( int offset, GSeekType whence = G_SEEK_SET );
    /**
    * Works like plain ftell
    */
    int tell() const;
    /**
    * The size of the region that's available to the user of this class.
    */
    size_t size() const;

    /**
    * Reads a bunch of bytes w/o endian conversion to the
    * given buffer, at most length bytes. The position in the stream
    * is changed, too.
    * Returns the number of bytes read.
    */
    size_t read( U8 *buffer, size_t length );

private:
    // It doesn't make sense to assign them (copying is fine, though)
    OLEImageReader& operator=( const OLEImageReader& rhs );

    // Updates the position, if it's valid. Returns false if the passed
    // position is out of the range.
    bool updatePosition( unsigned int position );

    OLEStreamReader& m_reader;
    const unsigned int m_start;
    const unsigned int m_limit;

    // Keeps track of the "virtual" position. We aren't allowed
    // to change the state of the real stream, so we have to push/pop
    // the real position every time one of the OLEImageReader methods
    // is called. We want to fake a consistent internal state, though,
    // so we have to remember the "virtual" position here.
    // Initialized with the m_start value.
    unsigned int m_position;
};

 
class OLEStreamWriter : public OLEStream
{
public:
    OLEStreamWriter( OLEStorage* storage );
    virtual ~OLEStreamWriter();

    /**
     * Is this still a valid stream?
     */
    virtual bool isValid() const = 0;

    /**
     * works like plain fseek
     */
    virtual bool seek( int offset, GSeekType whence = G_SEEK_SET ) = 0;
    /**
     * works like plain ftell
     */
    virtual int tell() const = 0;
    /**
     * The size of the stream
     */
    virtual size_t size() const = 0;

    /**
     * Writing to the current position
     * Note: Modifies the current position!
     * These write methods are endian-aware
     * and convert the contents to be LE in the file
     */
    virtual void write( U8 data ) = 0;
    /**
     * @see write(U8 data)
     */
    virtual void write( S8 data ) = 0;
    /**
     * @see write(U8 data)
     */
    virtual void write( U16 data ) = 0;
    /**
     * @see write(U8 data)
     */
    virtual void write( S16 data ) = 0;
    /**
     * @see write(U8 data)
     */
    virtual void write( U32 data ) = 0;
    /**
     * @see write(U8 data)
     */
    virtual void write( S32 data ) = 0;

    /**
     * Attention: This write method just writes out the
     * contents of the memory directly (w/o converting
     * to little-endian first!)
     */
    virtual void write( U8* data, size_t length ) = 0;

private:
    // we don't want to allow copying and assigning streams
    OLEStreamWriter( const OLEStreamWriter& rhs );
    OLEStreamWriter& operator=( const OLEStreamWriter& rhs );
};

} // namespace wvWare

#endif // OLESTREAM_H
