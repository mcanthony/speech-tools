/*************************************************************************/
/*                                                                       */
/*                Centre for Speech Technology Research                  */
/*                     University of Edinburgh, UK                       */
/*                      Copyright (c) 1995,1996                          */
/*                        All Rights Reserved.                           */
/*                                                                       */
/*  Permission is hereby granted, free of charge, to use and distribute  */
/*  this software and its documentation without restriction, including   */
/*  without limitation the rights to use, copy, modify, merge, publish,  */
/*  distribute, sublicense, and/or sell copies of this work, and to      */
/*  permit persons to whom this work is furnished to do so, subject to   */
/*  the following conditions:                                            */
/*   1. The code must retain the above copyright notice, this list of    */
/*      conditions and the following disclaimer.                         */
/*   2. Any modifications must be clearly marked as such.                */
/*   3. Original authors' names are not deleted.                         */
/*   4. The authors' names are not used to endorse or promote products   */
/*      derived from this software without specific prior written        */
/*      permission.                                                      */
/*                                                                       */
/*  THE UNIVERSITY OF EDINBURGH AND THE CONTRIBUTORS TO THIS WORK        */
/*  DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING      */
/*  ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT   */
/*  SHALL THE UNIVERSITY OF EDINBURGH NOR THE CONTRIBUTORS BE LIABLE     */
/*  FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES    */
/*  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN   */
/*  AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,          */
/*  ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF       */
/*  THIS SOFTWARE.                                                       */
/*                                                                       */
/*************************************************************************/
/*                     Author :  Paul Taylor                             */
/*                     Date   :  April 1995                              */
/*-----------------------------------------------------------------------*/
/*                  Vector/List convertion templates                     */
/* only include this if you define both vectors and lists for the class  */
/*                                                                       */
/*=======================================================================*/
#include <fstream.h>
#include "EST_TVector.h"
#include "EST_cutils.h"

template<class T> 
EST_TVector<T> &set(EST_TVector<T> &v, const EST_TList<T> &in)
{
  v.resize(in.length(), FALSE);
  EST_Litem *p;
  int i;
  for (i = 0, p = in.head(); p!= 0; p = next(p), ++i)
    v.a_no_check(i) = in.item(p);
  
  return v;
}

template<class T> EST_TVector<T> &copy(EST_TVector<T> a,const EST_TList<T> &in)
{
    a.resize(in.length(), FALSE);
    EST_Litem *p;
    for (i = 0, p = in.head(); p!= 0; p = next(p), ++i)
	a[i] = in.item(p);

    return a;
}
