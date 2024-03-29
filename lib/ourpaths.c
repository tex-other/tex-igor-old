/* ourpaths.c: path searching.  */

#include "config.h"

#include <kpathsea/kpathsea.h>

/* `path_dirs' is initialized in `setpaths', to a null-terminated array
   of directories to search for.  */
static const_string path_dirs[LAST_PATH];


/* This sets up the paths, by either copying from an environment variable
   or using the default path, which is defined as a preprocessor symbol
   (with the same name as the environment variable) in `site.h'.  The
   parameter PATH_BITS is a logical or of the paths we need to set.  */

extern void
setpaths (path_bits)
    int path_bits;
{
  if (path_bits & BIBINPUTPATHBIT)
    path_dirs[BIBINPUTPATH] = kpse_init_format (kpse_bib_format);

  if (path_bits & BSTINPUTPATHBIT)
    path_dirs[BSTINPUTPATH] = kpse_init_format (kpse_bst_format);

  if (path_bits & GFFILEPATHBIT)
    path_dirs[GFFILEPATH] = kpse_init_format (kpse_gf_format);

  if (path_bits & MFBASEPATHBIT)
    path_dirs[MFBASEPATH] = kpse_init_format (kpse_base_format);

  if (path_bits & MFINPUTPATHBIT)
    path_dirs[MFINPUTPATH] = kpse_init_format (kpse_mf_format);

  if (path_bits & MFPOOLPATHBIT)
    path_dirs[MFPOOLPATH] = kpse_init_format (kpse_mfpool_format);

  if (path_bits & PKFILEPATHBIT)
    path_dirs[PKFILEPATH] = kpse_init_format (kpse_pk_format);

  if (path_bits & TEXFORMATPATHBIT)
    path_dirs[TEXFORMATPATH] = kpse_init_format (kpse_fmt_format);

  if (path_bits & TEXINPUTPATHBIT)
    path_dirs[TEXINPUTPATH] = kpse_init_format (kpse_tex_format);

  if (path_bits & TEXPOOLPATHBIT)
    path_dirs[TEXPOOLPATH] = kpse_init_format (kpse_texpool_format);

  if (path_bits & TFMFILEPATHBIT)
    path_dirs[TFMFILEPATH] = kpse_init_format (kpse_tfm_format);

  if (path_bits & VFFILEPATHBIT)
    path_dirs[VFFILEPATH] = kpse_init_format (kpse_vf_format);
}

/* Look for NAME, a Pascal string, in the colon-separated list of
   directories given by `path_dirs[PATH_INDEX]'.  If the search is
   successful, leave the full pathname in NAME (which therefore must
   have enough room for such a pathname), padded with blanks.
   Otherwise, or if NAME is an absolute or relative pathname, just leave
   it alone.  */

boolean
testreadaccess (name, path_index)
    string name;
    int path_index;
{
  string found;  
  const_string path = path_dirs[path_index];
  
  make_c_string (&name);

  /* Look for it.  Don't use the kpse_find_glyph stuff, since we don't
     have the dpi available separately, and anyway we don't care about
     having pktogf run MakeTeXPK, etc.  */
  found = kpse_path_search (path, name, true);

  /* If we found it somewhere, save it.  */
  if (found)
    strcpy (name, found);
  
  make_pascal_string (&name);
  
  return found != NULL;
}
