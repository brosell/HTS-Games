
#ifndef CommentMacro_h
#define CommentMacro_h

// these two cause COMMENT to expand as '//' creating a source comment
#define SLASH(s) /##s
#define COMMENT SLASH(/)

/* in debug mode DEBUG_ONLY expads to nothing.
    So DEBUG_ONLY cerr << "debug" << endl; will print "debug" but in
    release mode it expands to 
    // cerr << "debug" << endl;
  */
#ifdef _DEBUG
#define DEBUG_ONLY
#else
#define DEBUG_ONLY COMMENT
#endif

#endif