/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org

Copyright (c) 2000-2014 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#ifndef _Ogre_AyncTicket_H_
#define _Ogre_AyncTicket_H_

#include "OgrePrerequisites.h"

namespace Ogre
{
    /** In Ogre 2.0 data structures, reading data from GPU back to CPU is asynchronous.
        @See BufferPacked::readRequest to generate a ticket. While the async transfer
        is being performed, you should be doing something else.
    @remarks
        If you call lock() before the transfer is done, it will produce a stall as the
        CPU must wait for the GPU to finish all its pending operations.
    @par
        Use @queryIsTransferDone to query if the transfer has finished. Beware not all
        APIs support querying async transfer status. In those cases there is no reliable
        way to determine when the transfer is done. An almost safe bet is to wait two
        frames before locking.
    @par
        Writing to the returned buffer by lock won't affect the contents in the GPU.
    @par
        Call @BufferPacked::disposeTicket when you're done with this ticket.
    */
    class AsyncTicket
    {
        bool mLocked;
        BufferPacked    *mCreator;

        size_t mElementStart;
        size_t mElementCount;

        virtual void* lockImpl(void) = 0;
        virtual void unlockImpl(void) = 0;

    public:

        virtual void* lock(void);
        virtual void unlock(void);

        virtual bool queryIsTransferDone(void) const        { return true; }
    };
}

#endif