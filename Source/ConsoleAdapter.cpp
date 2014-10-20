/******************************************************************************
Module:  ConsoleAdapter.cpp
Author:  
******************************************************************************/
#include "stdafx.h"
#include "ConsoleAdapter.h"
#include <fstream>
#include <tchar.h>

/////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ConsoleAdapter::ConsoleAdapter( bool bAutoDestroy ):
                                //m_fOldStdIn(0),
                                m_fpCRTIn(0),
                                m_nCRTIn(0),
                                //m_fOldStdOut(0),
                                m_fpCRTOut(0),
                                m_nCRTOut(0),
                                m_eConsoleType( BOTH ),
                                m_bDestroyed( false ),
                                m_bAutoDestroy( bAutoDestroy ),
                                m_hDumpConsole( 0 )
{
    
}

ConsoleAdapter::~ConsoleAdapter()
{
    if( m_bAutoDestroy || !m_bDestroyed)
        DestroyConsole();   
}

/******************************************************************************
Function: CreateConsole
Author  : Sudheesh.P.S
Param   : eConsoleType - Type of console(input/output or both)
Desc    : Allocates a new console and replaces the standard input/output streams
******************************************************************************/

bool ConsoleAdapter::CreateConsole( CONSOLETYPE_e eConsoleType )
{
    try
    {
        m_eConsoleType = eConsoleType;
        AllocConsole();
        return ReplaceHandles();
    }
    catch ( ... )
    {
        return false;
    }        
}

/******************************************************************************
Function: ReplaceHandles
Author  : Sudheesh.P.S
Desc    : Replaces the standard input/output streams
******************************************************************************/

bool ConsoleAdapter::ReplaceHandles()
{
    try
    {
        if( ( INPUT_CONS == m_eConsoleType ) || ( BOTH == m_eConsoleType ) )
        {
            m_nCRTIn= _open_osfhandle(
                 (long) GetStdHandle(STD_INPUT_HANDLE),
                 _O_TEXT );
            if( -1 == m_nCRTIn )
            {
                return false;
            }
            m_fpCRTIn = _fdopen( m_nCRTIn, "r" );
            if( !m_fpCRTIn )
            {
                return false;
            }
            m_fOldStdIn = *stdin;
            *stdin = *m_fpCRTIn;
            // if clear is not done, any cout statement before AllocConsole
            // will cause, the cin after AllocConsole to fail, so very important
            std::cin.clear();
        }
        if( ( OUTPUT_CONS == m_eConsoleType ) || ( BOTH == m_eConsoleType ) )
        {
            m_nCRTOut= _open_osfhandle(
                 (long) GetStdHandle(STD_OUTPUT_HANDLE),
                 _O_TEXT );
            if( -1 == m_nCRTOut )
            {
                return false;
            }
            
            m_fpCRTOut = _fdopen( m_nCRTOut, "w" );
            if( !m_fpCRTOut )
            {
                return false;
            }
            m_fOldStdOut = *stdout;
            *stdout = *m_fpCRTOut;
            // if clear is not done, any cout statement before AllocConsole
            // will cause, the cout after AllocConsole to fail, so very important
            std::cout.clear();
        }
    }
    catch ( ... )
    {
        return false;
    }        
    return true;
}

/******************************************************************************
Function: DestroyConsole
Author  : Sudheesh.P.S
Desc    : Destroys the attached console and restores the input/output handles
******************************************************************************/

void ConsoleAdapter::DestroyConsole()
{
    
    try
    {
        FreeConsole(); 
        if( 0 != m_hDumpConsole )
        {
            // Kill the DumpConsole when not needed
            TerminateProcess( m_hDumpConsole, 0 );
            CloseHandle( m_hDumpConsole );
            m_hDumpConsole = 0;
        }
        if( ( INPUT_CONS == m_eConsoleType ) || ( BOTH == m_eConsoleType ) )
        {
            if( 0 != m_fpCRTIn )
            {
                fclose( m_fpCRTIn );
            }
            _close( m_nCRTIn );
            *stdin = m_fOldStdIn;
        }
    
        if( ( OUTPUT_CONS == m_eConsoleType ) || ( BOTH == m_eConsoleType ) )
        {
            if( 0 != m_fpCRTOut )
            {
                fclose( m_fpCRTOut );
            }
            _close( m_nCRTOut );
            *stdout = m_fOldStdOut;
        }
        m_bDestroyed = true;
    }
    catch ( ... )
    {

    }
}
