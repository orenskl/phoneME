/*
 *  
 *
 * Copyright  1990-2007 Sun Microsystems, Inc. All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 only, as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License version 2 for more details (a copy is
 * included at /legal/license.txt).
 * 
 * You should have received a copy of the GNU General Public License
 * version 2 along with this work; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 * 
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa
 * Clara, CA 95054 or visit www.sun.com if you need additional
 * information or have any questions.
 */

#ifndef _PCSL_MEMORY_H_
#define _PCSL_MEMORY_H_

#include <string.h>
#include <stdlib.h>
/* autogenerated file */
#include <pcsl_config.h>
#include <pcsl_memory_impl.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup memory Memory Management Interfaces
 */

/**
 * @defgroup mem_high_interface High Level Interface
 * @ingroup memory
 */

/**
 * @defgroup mem_low_interface Low Level Interface
 * @ingroup memory
 */

/**
 * @file
 * @ingroup memory
 */

/**
 * @addtogroup mem_high_interface
 * @brief Interface for handling MIDP's/CLDC's memory pool.\n
 * ##include <pcsl_memory.h>
 *
 * Following functions represent public interfaces for memory management
 *
 * Allocate memory from the private PCSL memory pool. This implementation
 * needs to return a pointer to a valid block of memory, when passed an
 * allocation size of zero.
 * @param    size Number of byte to allocate
 * @return	  a pointer to the newly allocated memory
 *
 * <b>char* pcsl_mem_malloc(int size);</b>
 * 
 * Allocate memory from the private PCSL memory pool,
 * memory contents are cleared. This implementation
 * needs to return a pointer to a valid block of memory, when passed an
 * allocation size of zero.
 * @param    nelem Number of elements to allocate 
 * @param    elsize Size of one element 
 * @return	  pointer to the newly allocated and cleared memory 
 * 
 * <b>void* pcsl_mem_calloc(unsigned int nelem, unsigned int elsize);</b>
 *
 *  Re-allocates memory at the given pointer location from the private \n
 *  PCSL memory pool (or null for new memory) so that it is the given \n
 *  size. This implementation needs to return a pointer to a valid block
 *  of memory, even when the given size is zero.\n
 * @param  ptr		Original memory pointer
 * @param  size		New size 
 * @return	  pointer to the re-allocated memory 
 * 
 * <b>void* pcsl_mem_realloc(void* ptr, unsigned int size);</b>
 *
 * Duplicate the given string (allocates memory for the duplicate)
 * @param    s1	String to duplicate
 * @return	pointer to the duplicate string
 *
 * <b>char* pcsl_mem_strdup(const char *s1); </b>
 *
 * Free memory at the given pointer, from the private PCSL memory pool
 * When the given pointer is NULL, the implementation should handle it
 * without causing a runtime error.
 * @param    pt	Pointer to allocated memory
 * @return	<nothing>
 *
 * <b>void pcsl_mem_free(void *ptr); </b>
 *
 * Performs any needed memory system initialization. Must be called before any other pcsl
 * memory function. \n
 * NOTE: This must only be called once \n
 * @param    startAddr   Starting address of an already allocated  pool of memory. 
 *                       If NULL, then a pool of specified size will either be dynamically
 *                       or statically allocated.
 * @param    size	 Size of memory pool to use; if size is 0 or negative,
 *			 the default memory pool size chosen by the implementation
 *                       will be used.
 * @return	  0 on succes; non-zero otherwise
 *
 * <b>int pcsl_mem_initialize(void *startAddr, int size);</b>
 *
 * Takes any actions necessary to safely terminate the memory
 * subsystem.
 * @param  <none>
 * @return	  <nothing>
 *
 * <b>void pcsl_mem_finalize(); </b>
 *
 * Gets the maximum amount of heap space, in bytes, available to the system \n
 * for allocation. This value is constant throughout the lifetime of the
 * process.
 * @param    <none>
 * @return	  The maximum number of bytes available on the heap, or -1 if the
 *                information is not available.
 *
 * <b>int pcsl_mem_get_total_heap(); </b>
 *
 * Gets the current amount of unused heap space, in bytes. This value \n
 * changes with every <tt>pcsl_mem_malloc</tt> and <tt>pcsl_mem_free</tt>
 * function call.
 * @param    <none>
 * @return	  the number of bytes of heap space that are currently unused, or -1
 *                if the information is not available
 * <b>int pcsl_mem_get_free_heap(); </b>
 *
 * Displays the current state of the memory sub-system.
 *
 * @param  countMemoryLeaksOnly amount of data to gather: if is non-zero,
 *	  display allocated blocks of memory; otherwise display both allocated
 *	  and free blocks
 *
 * @return  the number of allocated blocks, or -1 if there was an error
 *
 * <b>int pcsl_mem_malloc_dump(int countMemoryLeaksOnly); </b>
 *
 * Allocate a memory chunk that can be shrunk, or expanded (up to max_size)
 * The returned pointer is <alignment>-bytes aligned.
 *
 * This function is called by the ObjectHeap class in the CLDC package 
 * to manage the memory space for the Java heap.
 *
 * @param initial_size Initial size of the memory chunk
 * @param max_size Maximum size
 * @param alignment Alignment
 *
 * @return Pointer to allocated memory chunk if successful
 *         NULL if unsucessful.
 *
 * <b>void* pcsl_mem_allocate_chunk(unsigned int initial_size,
 *                               unsigned int max_size, 
 *                               unsigned int alignment); </b>
 *
 * Expand or shrink a chunk returned by allocate_chunk().
 * The chunk is never moved.
 *
 * This function is called by the ObjectHeap class in the CLDC package 
 * to manage the memory space for the Java heap.
 *
 * @param chunk_ptr Pointer to memory chunk
 * @param new_size New size of the chunk
 * 
 * @return old size if successful; 0 if fails to expand (shrink will 
 * always succeed). 
 * 
 * <b>unsigned int pcsl_mem_adjust_chunk(void *chunk_ptr, unsigned int new_size);</b>
 *
 * Free a chunk returned by pcsl_allocate_chunk() 
 *
 * This function is called by the ObjectHeap class in the CLDC package 
 * to manage the memory space for the Java heap.
 *
 * @param chunk_ptr Pointer to memory chunk
 *
 * <b>void pcsl_mem_free_chunk(void *chunk_ptr);</b>
 * 
 */
#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
 * Setter of callback function, invoked when memory allocation from some lower
 * defined memory functions fails.
 */  
void set_pcsl_memory_allocationerror_callback(void (*callback_pointer)());

#ifdef PCSL_DEBUG

/** 
 * Allocates memory of the given size from the private PCSL memory
 * pool.
 */
void*
pcsl_mem_malloc(unsigned int size, char* filename, int lineno);

/** 
 * Allocates and clears the given number of elements of the given size
 * from the private PCSL memory pool.
 */
void*
pcsl_mem_calloc(unsigned int nelem, unsigned int elsize, 
                     char* filename, int lineno);
                     
/**
 * Re-allocates memory at the given pointer location in the private
 * PCSL memory pool (or null for new memory) so that it is the given
 * size.
 */
void*
pcsl_mem_realloc(void* ptr, unsigned int size, char* filename, int lineno);

/**
 * Duplicates the given string after allocating the memory for it.
 */
char*
pcsl_mem_strdup(const char *s1, char* filename, int lineno);

#else //! PCSL_DEBUG 

/** 
 * Allocates memory of the given size from the private PCSL memory
 * pool.
 */ 
void * pcsl_mem_malloc(unsigned int size);

/** 
 * Allocates and clears the given number of elements of the given size
 * from the private PCSL memory pool.
 */         
void * pcsl_mem_calloc(unsigned int nelem, unsigned int size);

/**
 * Re-allocates memory at the given pointer location in the private
 * PCSL memory pool (or null for new memory) so that it is the given
 * size.
 */ 
void * pcsl_mem_realloc(void * ptr, unsigned int size);

/**
 * Duplicates the given string after allocating the memory for it.
 */
char * pcsl_mem_strdup(const char * s1);

#endif //PCSL_DEBUG - #else


/**
 * Frees memory at the given pointer in the private PCSL memory pool.
 */
#define pcsl_mem_free(x)       pcsl_mem_free_impl((x))

/**
 * Initializes a PCSL memory pool.
 * <p><b>NOTE:</b> This function must only be called once.
 * 
 */
#define pcsl_mem_initialize(x, y) pcsl_mem_initialize_impl((x), (y))

/**
 * Takes any actions necessary to safely terminate the memory
 * subsystem.
 */
#define pcsl_mem_finalize() pcsl_mem_finalize_impl()

/**
 * Gets the maximum amount of heap space, in bytes, available to the system
 * for allocation. This value is constant throughout the lifetime of the
 * process.
 *
 */
#define pcsl_mem_get_total_heap()  pcsl_mem_get_total_heap_impl()

/**
 * Gets the current amount of unused heap space, in bytes. This value
 * changes with every <tt>pcslMalloc</tt> and <tt>pcslFree</tt>
 * function call.
 *
 */
#define pcsl_mem_get_free_heap()  pcsl_mem_get_free_heap_impl()

/**
 * Displays the current state of the memory sub-system. 
 * 
 */
#define pcsl_mem_malloc_dump(x)  pcsl_mem_malloc_dump_impl((x))


/**
 * Allocate a memory chunk that can be shrunk, or expanded (up to max_size)
 * The returned pointer is <alignment>-bytes aligned.
 *
 * This function is called by the ObjectHeap class in the CLDC package 
 * to manage the memory space for the Java heap.
 *
 * @param initial_size Initial size of the memory chunk
 * @param max_size Maximum size
 * @param alignment Alignment
 *
 * @return Pointer to allocated memory chunk if successful
 *         NULL if unsucessful.
 *
 */
extern void* pcsl_mem_allocate_chunk(unsigned int initial_size,
                                     unsigned int max_size, 
                                     unsigned int alignment);

/**
 * Expand or shrink a chunk returned by allocate_chunk().
 * The chunk is never moved.
 *
 * This function is called by the ObjectHeap class in the CLDC package 
 * to manage the memory space for the Java heap.
 *
 * @param chunk_ptr Pointer to memory chunk
 * @param new_size New size of the chunk
 * 
 * @return old size if successful; 0 if fails to expand (shrink will 
 * always succeed). 
 * 
 */
extern unsigned int pcsl_mem_adjust_chunk(void *chunk_ptr, unsigned int new_size);


/**
 * Free a chunk returned by pcsl_allocate_chunk() 
 *
 * This function is called by the ObjectHeap class in the CLDC package 
 * to manage the memory space for the Java heap.
 *
 * @param chunk_ptr Pointer to memory chunk
 *
 */
extern void pcsl_mem_free_chunk(void *chunk_ptr);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/**
 * @addtogroup mem_low_interface
 * @brief Low Level Interface using standard C library, \n
 * ##include <stdlib.h>
 *
 * For the <b>malloc</b> module, the low level interface consists of
 * standard C library memory functions <b>malloc</b>, <b>calloc</b>, <b>realloc</b>, <b>free</b>
 * and <b>strdup</b>. \n
 * For the <b>heap</b> module, if a static array is used as the memory pool, 
 * (PCSL_MEMORY_USE_STATIC is defined) no low level functions are needed. If a static
 * array is not being used, <b>malloc</b> and <b>free</b> will be needed. \n
 *
 * If one of the supplied memory modules is being used, then the target platform needs
 * to supply the above mentioned low level functions, specified below. 
 *
 * Allocate memory from the private PCSL memory pool. This implementation
 * needs to return a pointer to a valid block of memory, when passed an
 * allocation size of zero.
 * @param    size Number of byte to allocate
 * @return	  a pointer to the newly allocated memory
 *
 * <b>char* malloc(int size);</b>
 *
 * Allocate memory from the private PCSL memory pool,
 * memory contents are cleared. This implementation
 * needs to return a pointer to a valid block of memory, when passed an
 * allocation size of zero.
 * @param    nelem Number of elements to allocate
 * @param    elsize Size of one element
 * @return	  pointer to the newly allocated and cleared memory
 *
 * <b>void* calloc(unsigned int nelem, unsigned int elsize);</b>
 *
 *  Re-allocates memory at the given pointer location from the private \n
 *  PCSL memory pool (or null for new memory) so that it is the given \n
 *  size. This implementation needs to return a pointer to a valid block
 *  of memory, even when the given size is zero.\n
 * @param  ptr		Original memory pointer
 * @param  size		New size
 * @return	  pointer to the re-allocated memory
 *
 * <b>void* realloc(void* ptr, unsigned int size);</b>
 *
 * Duplicate the given string (allocates memory for the duplicate)
 * @param    s1 String to duplicate
 * @return	pointer to the duplicate string
 *
 * <b>char* strdup(const char *s1); </b>
 *
 * Free memory at the given pointer, from the private PCSL memory pool
 * When the given pointer is NULL, the implementation should handle it
 * without causing a runtime error.
 * @param    pt Pointer to allocated memory
 * @return	<nothing>
 *
 * <b>void free(void *ptr); </b>
 */

#ifdef __cplusplus
}
#endif

#endif /* _PCSL_MEMORY_H_ */


