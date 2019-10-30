/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 11:57:00 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/30 17:04:23 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUSTOM__H
# define _CUSTOM__H

typedef int	cpu_type_t;
typedef int	cpu_subtype_t;
typedef int vm_prot_t;

struct mach_header {
	uint32_t	magic;		/* mach magic number identifier */
	cpu_type_t	cputype;	/* cpu specifier */
	cpu_subtype_t	cpusubtype;	/* machine specifier */
	uint32_t	filetype;	/* type of file */
	uint32_t	ncmds;		/* number of load commands */
	uint32_t	sizeofcmds;	/* the size of all the load commands */
	uint32_t	flags;		/* flags */
};

struct mach_header_64 {
	uint32_t	magic;		/* mach magic number identifier */
	cpu_type_t	cputype;	/* cpu specifier */
	cpu_subtype_t	cpusubtype;	/* machine specifier */
	uint32_t	filetype;	/* type of file */
	uint32_t	ncmds;		/* number of load commands */
	uint32_t	sizeofcmds;	/* the size of all the load commands */
	uint32_t	flags;		/* flags */
	uint32_t	reserved;	/* reserved */
};

struct fat_header {
    uint32_t        magic;      /* FAT_MAGIC or FAT_MAGIC_64 */
    uint32_t        nfat_arch;  /* number of structs that follow */
};

struct fat_arch {                /* struct fat_arch_64 for 64-bit*/
    cpu_type_t      cputype;    /* cpu specifier (int) */
    cpu_subtype_t   cpusubtype; /* machine specifier (int) */
	uint32_t        offset;     /* file offset to this object file */
	uint32_t        size;       /* size of this object file */
    uint32_t        align;      /* alignment as a power of 2 */
};

struct fat_arch_64 {                /* struct fat_arch_64 for 64-bit*/
    cpu_type_t      cputype;    /* cpu specifier (int) */
    cpu_subtype_t   cpusubtype; /* machine specifier (int) */
	uint64_t        offset;     /* file offset to this object file */
	uint64_t        size;       /* size of this object file */
    uint32_t        align;      /* alignment as a power of 2 */
    uint32_t        reserved;      /* alignment as a power of 2 */
};

/*
 *	Machine types known by all.
 */
 
#define CPU_TYPE_ANY		((cpu_type_t) -1)

#define CPU_TYPE_VAX		((cpu_type_t) 1)
#define CPU_TYPE_ROMP		((cpu_type_t) 2)
#define CPU_TYPE_NS32032	((cpu_type_t) 4)
#define CPU_TYPE_NS32332        ((cpu_type_t) 5)
#define	CPU_TYPE_MC680x0	((cpu_type_t) 6)
#define CPU_TYPE_I386		((cpu_type_t) 7)
#define CPU_TYPE_X86_64		((cpu_type_t) (CPU_TYPE_I386 | CPU_ARCH_ABI64))
#define CPU_TYPE_MIPS		((cpu_type_t) 8)
#define CPU_TYPE_NS32532        ((cpu_type_t) 9)
#define CPU_TYPE_HPPA           ((cpu_type_t) 11)
#define CPU_TYPE_ARM		((cpu_type_t) 12)
#define CPU_TYPE_MC88000	((cpu_type_t) 13)
#define CPU_TYPE_SPARC		((cpu_type_t) 14)
#define CPU_TYPE_I860		((cpu_type_t) 15) // big-endian
#define	CPU_TYPE_I860_LITTLE	((cpu_type_t) 16) // little-endian
#define CPU_TYPE_RS6000		((cpu_type_t) 17)
#define CPU_TYPE_MC98000	((cpu_type_t) 18)
#define CPU_TYPE_POWERPC	((cpu_type_t) 18)
#define CPU_ARCH_ABI64		 0x1000000
#define CPU_TYPE_POWERPC64	((cpu_type_t)(CPU_TYPE_POWERPC | CPU_ARCH_ABI64))
#define CPU_TYPE_VEO		((cpu_type_t) 255)
#define CPU_TYPE_ARM64		((cpu_type_t)(CPU_TYPE_ARM | CPU_ARCH_ABI64))
		

/*
 *	Machine subtypes (these are defined here, instead of in a machine
 *	dependent directory, so that any program can get all definitions
 *	regardless of where is it compiled).
 */

/*
 * Capability bits used in the definition of cpu_subtype.
 */
#define CPU_SUBTYPE_MASK       0xff000000      /* mask for feature flags */
#define CPU_SUBTYPE_LIB64      0x80000000      /* 64 bit libraries */


/*
 *	Object files that are hand-crafted to run on any
 *	implementation of an architecture are tagged with
 *	CPU_SUBTYPE_MULTIPLE.  This functions essentially the same as
 *	the "ALL" subtype of an architecture except that it allows us
 *	to easily find object files that may need to be modified
 *	whenever a new implementation of an architecture comes out.
 *
 *	It is the responsibility of the implementor to make sure the
 *	software handles unsupported implementations elegantly.
 */
#define	CPU_SUBTYPE_MULTIPLE	((cpu_subtype_t) -1)


/*
 *	VAX subtypes (these do *not* necessary conform to the actual cpu
 *	ID assigned by DEC available via the SID register).
 */

#define	CPU_SUBTYPE_VAX_ALL	((cpu_subtype_t) 0) 
#define CPU_SUBTYPE_VAX780	((cpu_subtype_t) 1)
#define CPU_SUBTYPE_VAX785	((cpu_subtype_t) 2)
#define CPU_SUBTYPE_VAX750	((cpu_subtype_t) 3)
#define CPU_SUBTYPE_VAX730	((cpu_subtype_t) 4)
#define CPU_SUBTYPE_UVAXI	((cpu_subtype_t) 5)
#define CPU_SUBTYPE_UVAXII	((cpu_subtype_t) 6)
#define CPU_SUBTYPE_VAX8200	((cpu_subtype_t) 7)
#define CPU_SUBTYPE_VAX8500	((cpu_subtype_t) 8)
#define CPU_SUBTYPE_VAX8600	((cpu_subtype_t) 9)
#define CPU_SUBTYPE_VAX8650	((cpu_subtype_t) 10)
#define CPU_SUBTYPE_VAX8800	((cpu_subtype_t) 11)
#define CPU_SUBTYPE_UVAXIII	((cpu_subtype_t) 12)

/*
 *	ROMP subtypes.
 */

#define	CPU_SUBTYPE_RT_ALL	((cpu_subtype_t) 0)
#define CPU_SUBTYPE_RT_PC	((cpu_subtype_t) 1)
#define CPU_SUBTYPE_RT_APC	((cpu_subtype_t) 2)
#define CPU_SUBTYPE_RT_135	((cpu_subtype_t) 3)

/*
 *	32032/32332/32532 subtypes.
 */

#define	CPU_SUBTYPE_MMAX_ALL	    ((cpu_subtype_t) 0)
#define CPU_SUBTYPE_MMAX_DPC	    ((cpu_subtype_t) 1)	/* 032 CPU */
#define CPU_SUBTYPE_SQT		    ((cpu_subtype_t) 2)
#define CPU_SUBTYPE_MMAX_APC_FPU    ((cpu_subtype_t) 3)	/* 32081 FPU */
#define CPU_SUBTYPE_MMAX_APC_FPA    ((cpu_subtype_t) 4)	/* Weitek FPA */
#define CPU_SUBTYPE_MMAX_XPC	    ((cpu_subtype_t) 5)	/* 532 CPU */

/*
 *	I386 subtypes.
 */

#define	CPU_SUBTYPE_I386_ALL	((cpu_subtype_t) 3)
#define	CPU_SUBTYPE_X86_64_ALL	CPU_SUBTYPE_I386_ALL
#define CPU_SUBTYPE_386		((cpu_subtype_t) 3)
#define CPU_SUBTYPE_486		((cpu_subtype_t) 4)
#define CPU_SUBTYPE_486SX	((cpu_subtype_t) 4 + 128)
#define CPU_SUBTYPE_586		((cpu_subtype_t) 5)
#define CPU_SUBTYPE_INTEL(f, m)	((cpu_subtype_t) (f) + ((m) << 4))
#define CPU_SUBTYPE_PENT	CPU_SUBTYPE_INTEL(5, 0)
#define CPU_SUBTYPE_PENTPRO	CPU_SUBTYPE_INTEL(6, 1)
#define CPU_SUBTYPE_PENTII_M3	CPU_SUBTYPE_INTEL(6, 3)
#define CPU_SUBTYPE_PENTII_M5	CPU_SUBTYPE_INTEL(6, 5)
#define CPU_SUBTYPE_PENTIUM_4	CPU_SUBTYPE_INTEL(10, 0)

#define CPU_SUBTYPE_INTEL_FAMILY(x)	((x) & 15)
#define CPU_SUBTYPE_INTEL_FAMILY_MAX	15

#define CPU_SUBTYPE_INTEL_MODEL(x)	((x) >> 4)
#define CPU_SUBTYPE_INTEL_MODEL_ALL	0

#define CPU_SUBTYPE_X86_64_H	((cpu_subtype_t)8) /* Haswell and compatible */

/*
 *	Mips subtypes.
 */

#define	CPU_SUBTYPE_MIPS_ALL	((cpu_subtype_t) 0)
#define CPU_SUBTYPE_MIPS_R2300	((cpu_subtype_t) 1)
#define CPU_SUBTYPE_MIPS_R2600	((cpu_subtype_t) 2)
#define CPU_SUBTYPE_MIPS_R2800	((cpu_subtype_t) 3)
#define CPU_SUBTYPE_MIPS_R2000a	((cpu_subtype_t) 4)

/*
 * 	680x0 subtypes
 *
 * The subtype definitions here are unusual for historical reasons.
 * NeXT used to consider 68030 code as generic 68000 code.  For
 * backwards compatability:
 * 
 *	CPU_SUBTYPE_MC68030 symbol has been preserved for source code
 *	compatability.
 *
 *	CPU_SUBTYPE_MC680x0_ALL has been defined to be the same
 *	subtype as CPU_SUBTYPE_MC68030 for binary comatability.
 *
 *	CPU_SUBTYPE_MC68030_ONLY has been added to allow new object
 *	files to be tagged as containing 68030-specific instructions.
 */

#define	CPU_SUBTYPE_MC680x0_ALL		((cpu_subtype_t) 1)
#define CPU_SUBTYPE_MC68030		((cpu_subtype_t) 1) /* compat */
#define CPU_SUBTYPE_MC68040		((cpu_subtype_t) 2) 
#define	CPU_SUBTYPE_MC68030_ONLY	((cpu_subtype_t) 3)

/*
 *	HPPA subtypes for Hewlett-Packard HP-PA family of
 *	risc processors. Port by NeXT to 700 series. 
 */

#define	CPU_SUBTYPE_HPPA_ALL		((cpu_subtype_t) 0)
#define CPU_SUBTYPE_HPPA_7100		((cpu_subtype_t) 0) /* compat */
#define CPU_SUBTYPE_HPPA_7100LC		((cpu_subtype_t) 1)

/* 
 * 	Acorn subtypes - Acorn Risc Machine port done by
 *		Olivetti System Software Laboratory
 */

#define	CPU_SUBTYPE_ARM_ALL		((cpu_subtype_t) 0)
#define CPU_SUBTYPE_ARM_A500_ARCH	((cpu_subtype_t) 1)
#define CPU_SUBTYPE_ARM_A500		((cpu_subtype_t) 2)
#define CPU_SUBTYPE_ARM_A440		((cpu_subtype_t) 3)
#define CPU_SUBTYPE_ARM_M4		((cpu_subtype_t) 4)
#define CPU_SUBTYPE_ARM_V4T		((cpu_subtype_t) 5)
#define CPU_SUBTYPE_ARM_V6		((cpu_subtype_t) 6)
#define CPU_SUBTYPE_ARM_V5TEJ		((cpu_subtype_t) 7)
#define CPU_SUBTYPE_ARM_XSCALE		((cpu_subtype_t) 8)
#define CPU_SUBTYPE_ARM_V7		((cpu_subtype_t) 9)
#define CPU_SUBTYPE_ARM_V7F		((cpu_subtype_t) 10) /* Cortex A9 */
#define CPU_SUBTYPE_ARM_V7S		((cpu_subtype_t) 11) /* Swift */
#define CPU_SUBTYPE_ARM_V7K		((cpu_subtype_t) 12) /* Kirkwood40 */
#define CPU_SUBTYPE_ARM_V6M		((cpu_subtype_t) 14) /* Not meant to be run under xnu */
#define CPU_SUBTYPE_ARM_V7M		((cpu_subtype_t) 15) /* Not meant to be run under xnu */
#define CPU_SUBTYPE_ARM_V7EM		((cpu_subtype_t) 16) /* Not meant to be run under xnu */
#define CPU_SUBTYPE_ARM_V8		((cpu_subtype_t) 13)

#define	CPU_SUBTYPE_ARM64_ALL		((cpu_subtype_t) 0)
#define	CPU_SUBTYPE_ARM64_V8		((cpu_subtype_t) 1)

/*
 *	MC88000 subtypes
 */
#define	CPU_SUBTYPE_MC88000_ALL	((cpu_subtype_t) 0)
#define CPU_SUBTYPE_MMAX_JPC	((cpu_subtype_t) 1)
#define CPU_SUBTYPE_MC88100	((cpu_subtype_t) 1)
#define CPU_SUBTYPE_MC88110	((cpu_subtype_t) 2)

/*
 *	MC98000 (PowerPC) subtypes
 */
#define	CPU_SUBTYPE_MC98000_ALL	((cpu_subtype_t) 0)
#define CPU_SUBTYPE_MC98601	((cpu_subtype_t) 1)

/*
 *	I860 subtypes
 */
#define CPU_SUBTYPE_I860_ALL	((cpu_subtype_t) 0)
#define CPU_SUBTYPE_I860_860	((cpu_subtype_t) 1)

/*
 * 	I860 subtypes for NeXT-internal backwards compatability.
 *	These constants will be going away.  DO NOT USE THEM!!!
 */
#define CPU_SUBTYPE_LITTLE_ENDIAN	((cpu_subtype_t) 0)
#define CPU_SUBTYPE_BIG_ENDIAN		((cpu_subtype_t) 1)

/*
 *	I860_LITTLE subtypes
 */
#define	CPU_SUBTYPE_I860_LITTLE_ALL	((cpu_subtype_t) 0)
#define	CPU_SUBTYPE_I860_LITTLE	((cpu_subtype_t) 1)

/*
 *	RS6000 subtypes
 */
#define	CPU_SUBTYPE_RS6000_ALL	((cpu_subtype_t) 0)
#define CPU_SUBTYPE_RS6000	((cpu_subtype_t) 1)

/*
 *	Sun4 subtypes - port done at CMU
 */
#define	CPU_SUBTYPE_SUN4_ALL		((cpu_subtype_t) 0)
#define CPU_SUBTYPE_SUN4_260		((cpu_subtype_t) 1)
#define CPU_SUBTYPE_SUN4_110		((cpu_subtype_t) 2)

#define	CPU_SUBTYPE_SPARC_ALL		((cpu_subtype_t) 0)

/*
 *      PowerPC subtypes
 */
#define CPU_SUBTYPE_POWERPC_ALL		((cpu_subtype_t) 0)
#define CPU_SUBTYPE_POWERPC_601		((cpu_subtype_t) 1)
#define CPU_SUBTYPE_POWERPC_602		((cpu_subtype_t) 2)
#define CPU_SUBTYPE_POWERPC_603		((cpu_subtype_t) 3)
#define CPU_SUBTYPE_POWERPC_603e	((cpu_subtype_t) 4)
#define CPU_SUBTYPE_POWERPC_603ev	((cpu_subtype_t) 5)
#define CPU_SUBTYPE_POWERPC_604		((cpu_subtype_t) 6)
#define CPU_SUBTYPE_POWERPC_604e	((cpu_subtype_t) 7)
#define CPU_SUBTYPE_POWERPC_620		((cpu_subtype_t) 8)
#define CPU_SUBTYPE_POWERPC_750		((cpu_subtype_t) 9)
#define CPU_SUBTYPE_POWERPC_7400	((cpu_subtype_t) 10)
#define CPU_SUBTYPE_POWERPC_7450	((cpu_subtype_t) 11)
#define CPU_SUBTYPE_POWERPC_970		((cpu_subtype_t) 100)

/*
 * VEO subtypes
 * Note: the CPU_SUBTYPE_VEO_ALL will likely change over time to be defined as
 * one of the specific subtypes.
 */
#define CPU_SUBTYPE_VEO_1	((cpu_subtype_t) 1)
#define CPU_SUBTYPE_VEO_2	((cpu_subtype_t) 2)
#define CPU_SUBTYPE_VEO_3	((cpu_subtype_t) 3)
#define CPU_SUBTYPE_VEO_4	((cpu_subtype_t) 4)
#define CPU_SUBTYPE_VEO_ALL	CPU_SUBTYPE_VEO_2


#define MH_MAGIC    0xfeedface
#define MH_CIGAM    0xcefaedfe
#define MH_MAGIC_64 0xfeedfacf
#define MH_CIGAM_64 0xcffaedfe
#define FAT_MAGIC    0xcafebabe    /* the fat magic number */
#define FAT_CIGAM    0xbebafeca    /* NXSwapLong(FAT_MAGIC) */
#define FAT_MAGIC_64 0xcafebabf    /* the 64-bit fat magic number */
#define FAT_CIGAM_64 0xbfbafeca    /* NXSwapLong(FAT_MAGIC_64) */

#define	MH_OBJECT	0x1		/* relocatable object file */
#define	MH_EXECUTE	0x2		/* demand paged executable file */
#define	MH_FVMLIB	0x3		/* fixed VM shared library file */
#define	MH_CORE		0x4		/* core file */
#define	MH_PRELOAD	0x5		/* preloaded executable file */
#define	MH_DYLIB	0x6		/* dynamically bound shared library */
#define	MH_DYLINKER	0x7		/* dynamic link editor */
#define	MH_BUNDLE	0x8		/* dynamically bound bundle file */
#define	MH_DYLIB_STUB	0x9		/* shared library stub for static */
					/*  linking only, no section contents */
#define	MH_DSYM		0xa		/* companion file with only debug */
					/*  sections */
#define	MH_KEXT_BUNDLE	0xb		/* x86_64 kexts */

/* Constants for the flags field of the mach_header */
#define	MH_NOUNDEFS	0x1		/* the object file has no undefined
					   references */
#define	MH_INCRLINK	0x2		/* the object file is the output of an
					   incremental link against a base file
					   and can't be link edited again */
#define MH_DYLDLINK	0x4		/* the object file is input for the
					   dynamic linker and can't be staticly
					   link edited again */
#define MH_BINDATLOAD	0x8		/* the object file's undefined
					   references are bound by the dynamic
					   linker when loaded. */
#define MH_PREBOUND	0x10		/* the file has its dynamic undefined
					   references prebound. */
#define MH_SPLIT_SEGS	0x20		/* the file has its read-only and
					   read-write segments split */
#define MH_LAZY_INIT	0x40		/* the shared library init routine is
					   to be run lazily via catching memory
					   faults to its writeable segments
					   (obsolete) */
#define MH_TWOLEVEL	0x80		/* the image is using two-level name
					   space bindings */
#define MH_FORCE_FLAT	0x100		/* the executable is forcing all images
					   to use flat name space bindings */
#define MH_NOMULTIDEFS	0x200		/* this umbrella guarantees no multiple
					   defintions of symbols in its
					   sub-images so the two-level namespace
					   hints can always be used. */
#define MH_NOFIXPREBINDING 0x400	/* do not have dyld notify the
					   prebinding agent about this
					   executable */
#define MH_PREBINDABLE  0x800           /* the binary is not prebound but can
					   have its prebinding redone. only used
                                           when MH_PREBOUND is not set. */
#define MH_ALLMODSBOUND 0x1000		/* indicates that this binary binds to
                                           all two-level namespace modules of
					   its dependent libraries. only used
					   when MH_PREBINDABLE and MH_TWOLEVEL
					   are both set. */
#define MH_SUBSECTIONS_VIA_SYMBOLS 0x2000/* safe to divide up the sections into
					    sub-sections via symbols for dead
					    code stripping */
#define MH_CANONICAL    0x4000		/* the binary has been canonicalized
					   via the unprebind operation */
#define MH_WEAK_DEFINES	0x8000		/* the final linked image contains
					   external weak symbols */
#define MH_BINDS_TO_WEAK 0x10000	/* the final linked image uses
					   weak symbols */

#define MH_ALLOW_STACK_EXECUTION 0x20000/* When this bit is set, all stacks
					   in the task will be given stack
					   execution privilege.  Only used in
					   MH_EXECUTE filetypes. */
#define MH_ROOT_SAFE 0x40000           /* When this bit is set, the binary
					  declares it is safe for use in
					  processes with uid zero */

#define MH_SETUID_SAFE 0x80000         /* When this bit is set, the binary
					  declares it is safe for use in
					  processes when issetugid() is true */

#define MH_NO_REEXPORTED_DYLIBS 0x100000 /* When this bit is set on a dylib,
					  the static linker does not need to
					  examine dependent dylibs to see
					  if any are re-exported */
#define	MH_PIE 0x200000			/* When this bit is set, the OS will
					   load the main executable at a
					   random address.  Only used in
					   MH_EXECUTE filetypes. */
#define	MH_DEAD_STRIPPABLE_DYLIB 0x400000 /* Only for use on dylibs.  When
					     linking against a dylib that
					     has this bit set, the static linker
					     will automatically not create a
					     LC_LOAD_DYLIB load command to the
					     dylib if no symbols are being
					     referenced from the dylib. */
#define MH_HAS_TLV_DESCRIPTORS 0x800000 /* Contains a section of type
					    S_THREAD_LOCAL_VARIABLES */

#define MH_NO_HEAP_EXECUTION 0x1000000	/* When this bit is set, the OS will
					   run the main executable with
					   a non-executable heap even on
					   platforms (e.g. i386) that don't
					   require it. Only used in MH_EXECUTE
					   filetypes. */

#define MH_APP_EXTENSION_SAFE 0x02000000 /* The code was linked for use in an
					    application extension. */

#define	MH_NLIST_OUTOFSYNC_WITH_DYLDINFO 0x04000000
					/* The external symbols listed in the nlist
   					   symbol table do not include all the symbols
					   listed in the dyld info. */

#define	MH_SIM_SUPPORT 0x08000000

struct load_command {
	uint32_t cmd;		/* type of load command */
	uint32_t cmdsize;	/* total size of command in bytes */
};

#define LC_REQ_DYLD 0x80000000

/* Constants for the cmd field of all load commands, the type */
#define	LC_SEGMENT	0x1	/* segment of this file to be mapped */
#define	LC_SYMTAB	0x2	/* link-edit stab symbol table info */
#define	LC_SYMSEG	0x3	/* link-edit gdb symbol table info (obsolete) */
#define	LC_THREAD	0x4	/* thread */
#define	LC_UNIXTHREAD	0x5	/* unix thread (includes a stack) */
#define	LC_LOADFVMLIB	0x6	/* load a specified fixed VM shared library */
#define	LC_IDFVMLIB	0x7	/* fixed VM shared library identification */
#define	LC_IDENT	0x8	/* object identification info (obsolete) */
#define LC_FVMFILE	0x9	/* fixed VM file inclusion (internal use) */
#define LC_PREPAGE      0xa     /* prepage command (internal use) */
#define	LC_DYSYMTAB	0xb	/* dynamic link-edit symbol table info */
#define	LC_LOAD_DYLIB	0xc	/* load a dynamically linked shared library */
#define	LC_ID_DYLIB	0xd	/* dynamically linked shared lib ident */
#define LC_LOAD_DYLINKER 0xe	/* load a dynamic linker */
#define LC_ID_DYLINKER	0xf	/* dynamic linker identification */
#define	LC_PREBOUND_DYLIB 0x10	/* modules prebound for a dynamically */
				/*  linked shared library */
#define	LC_ROUTINES	0x11	/* image routines */
#define	LC_SUB_FRAMEWORK 0x12	/* sub framework */
#define	LC_SUB_UMBRELLA 0x13	/* sub umbrella */
#define	LC_SUB_CLIENT	0x14	/* sub client */
#define	LC_SUB_LIBRARY  0x15	/* sub library */
#define	LC_TWOLEVEL_HINTS 0x16	/* two-level namespace lookup hints */
#define	LC_PREBIND_CKSUM  0x17	/* prebind checksum */


#define	LC_LOAD_WEAK_DYLIB (0x18 | LC_REQ_DYLD)

#define	LC_SEGMENT_64	0x19	/* 64-bit segment of this file to be
				   mapped */
#define	LC_ROUTINES_64	0x1a	/* 64-bit image routines */
#define LC_UUID		0x1b	/* the uuid */
#define LC_RPATH       (0x1c | LC_REQ_DYLD)    /* runpath additions */
#define LC_CODE_SIGNATURE 0x1d	/* local of code signature */
#define LC_SEGMENT_SPLIT_INFO 0x1e /* local of info to split segments */
#define LC_REEXPORT_DYLIB (0x1f | LC_REQ_DYLD) /* load and re-export dylib */
#define	LC_LAZY_LOAD_DYLIB 0x20	/* delay load of dylib until first use */
#define	LC_ENCRYPTION_INFO 0x21	/* encrypted segment information */
#define	LC_DYLD_INFO 	0x22	/* compressed dyld information */
#define	LC_DYLD_INFO_ONLY (0x22|LC_REQ_DYLD)	/* compressed dyld information only */
#define	LC_LOAD_UPWARD_DYLIB (0x23 | LC_REQ_DYLD) /* load upward dylib */
#define LC_VERSION_MIN_MACOSX 0x24   /* build for MacOSX min OS version */
#define LC_VERSION_MIN_IPHONEOS 0x25 /* build for iPhoneOS min OS version */
#define LC_FUNCTION_STARTS 0x26 /* compressed table of function start addresses */
#define LC_DYLD_ENVIRONMENT 0x27 /* string for dyld to treat
				    like environment variable */
#define LC_MAIN (0x28|LC_REQ_DYLD) /* replacement for LC_UNIXTHREAD */
#define LC_DATA_IN_CODE 0x29 /* table of non-instructions in __text */
#define LC_SOURCE_VERSION 0x2A /* source version used to build binary */
#define LC_DYLIB_CODE_SIGN_DRS 0x2B /* Code signing DRs copied from linked dylibs */
#define	LC_ENCRYPTION_INFO_64 0x2C /* 64-bit encrypted segment information */
#define LC_LINKER_OPTION 0x2D /* linker options in MH_OBJECT files */
#define LC_LINKER_OPTIMIZATION_HINT 0x2E /* optimization hints in MH_OBJECT files */
#define LC_VERSION_MIN_TVOS 0x2F /* build for AppleTV min OS version */
#define LC_VERSION_MIN_WATCHOS 0x30 /* build for Watch min OS version */
#define LC_NOTE 0x31 /* arbitrary data included within a Mach-O file */
#define LC_BUILD_VERSION 0x32 /* build for platform min OS version */
#define LC_DYLD_EXPORTS_TRIE (0x33 | LC_REQ_DYLD) /* used with linkedit_data_command, payload is trie */
#define LC_DYLD_CHAINED_FIXUPS (0x34 | LC_REQ_DYLD) /* used with linkedit_data_command */

union lc_str {
	uint32_t	offset;	/* offset to the string */
#ifndef __LP64__
	char		*ptr;	/* pointer to the string */
#endif 
};

struct segment_command { /* for 32-bit architectures */
	uint32_t	cmd;		/* LC_SEGMENT */
	uint32_t	cmdsize;	/* includes sizeof section structs */
	char		segname[16];	/* segment name */
	uint32_t	vmaddr;		/* memory address of this segment */
	uint32_t	vmsize;		/* memory size of this segment */
	uint32_t	fileoff;	/* file offset of this segment */
	uint32_t	filesize;	/* amount to map from the file */
	vm_prot_t	maxprot;	/* maximum VM protection */
	vm_prot_t	initprot;	/* initial VM protection */
	uint32_t	nsects;		/* number of sections in segment */
	uint32_t	flags;		/* flags */
};

/*
 * The 64-bit segment load command indicates that a part of this file is to be
 * mapped into a 64-bit task's address space.  If the 64-bit segment has
 * sections then section_64 structures directly follow the 64-bit segment
 * command and their size is reflected in cmdsize.
 */
struct segment_command_64 { /* for 64-bit architectures */
	uint32_t	cmd;		/* LC_SEGMENT_64 */
	uint32_t	cmdsize;	/* includes sizeof section_64 structs */
	char		segname[16];	/* segment name */
	uint64_t	vmaddr;		/* memory address of this segment */
	uint64_t	vmsize;		/* memory size of this segment */
	uint64_t	fileoff;	/* file offset of this segment */
	uint64_t	filesize;	/* amount to map from the file */
	vm_prot_t	maxprot;	/* maximum VM protection */
	vm_prot_t	initprot;	/* initial VM protection */
	uint32_t	nsects;		/* number of sections in segment */
	uint32_t	flags;		/* flags */
};

/* Constants for the flags field of the segment_command */
#define	SG_HIGHVM	0x1	/* the file contents for this segment is for
				   the high part of the VM space, the low part
				   is zero filled (for stacks in core files) */
#define	SG_FVMLIB	0x2	/* this segment is the VM that is allocated by
				   a fixed VM library, for overlap checking in
				   the link editor */
#define	SG_NORELOC	0x4	/* this segment has nothing that was relocated
				   in it and nothing relocated to it, that is
				   it maybe safely replaced without relocation*/
#define SG_PROTECTED_VERSION_1	0x8 /* This segment is protected.  If the
				       segment starts at file offset 0, the
				       first page of the segment is not
				       protected.  All other pages of the
				       segment are protected. */
#define SG_READ_ONLY    0x10 /* This segment is made read-only after fixups */


struct section { /* for 32-bit architectures */
	char		sectname[16];	/* name of this section */
	char		segname[16];	/* segment this section goes in */
	uint32_t	addr;		/* memory address of this section */
	uint32_t	size;		/* size in bytes of this section */
	uint32_t	offset;		/* file offset of this section */
	uint32_t	align;		/* section alignment (power of 2) */
	uint32_t	reloff;		/* file offset of relocation entries */
	uint32_t	nreloc;		/* number of relocation entries */
	uint32_t	flags;		/* flags (section type and attributes)*/
	uint32_t	reserved1;	/* reserved (for offset or index) */
	uint32_t	reserved2;	/* reserved (for count or sizeof) */
};

struct section_64 { /* for 64-bit architectures */
	char		sectname[16];	/* name of this section */
	char		segname[16];	/* segment this section goes in */
	uint64_t	addr;		/* memory address of this section */
	uint64_t	size;		/* size in bytes of this section */
	uint32_t	offset;		/* file offset of this section */
	uint32_t	align;		/* section alignment (power of 2) */
	uint32_t	reloff;		/* file offset of relocation entries */
	uint32_t	nreloc;		/* number of relocation entries */
	uint32_t	flags;		/* flags (section type and attributes)*/
	uint32_t	reserved1;	/* reserved (for offset or index) */
	uint32_t	reserved2;	/* reserved (for count or sizeof) */
	uint32_t	reserved3;	/* reserved */
};

/*
 * The flags field of a section structure is separated into two parts a section
 * type and section attributes.  The section types are mutually exclusive (it
 * can only have one type) but the section attributes are not (it may have more
 * than one attribute).
 */
#define SECTION_TYPE		 0x000000ff	/* 256 section types */
#define SECTION_ATTRIBUTES	 0xffffff00	/*  24 section attributes */

/* Constants for the type of a section */
#define	S_REGULAR		0x0	/* regular section */
#define	S_ZEROFILL		0x1	/* zero fill on demand section */
#define	S_CSTRING_LITERALS	0x2	/* section with only literal C strings*/
#define	S_4BYTE_LITERALS	0x3	/* section with only 4 byte literals */
#define	S_8BYTE_LITERALS	0x4	/* section with only 8 byte literals */
#define	S_LITERAL_POINTERS	0x5	/* section with only pointers to */
					/*  literals */

/* The currently known segment names and the section names in those segments */

#define	SEG_PAGEZERO	"__PAGEZERO"	/* the pagezero segment which has no */
					/* protections and catches NULL */
					/* references for MH_EXECUTE files */


#define	SEG_TEXT	"__TEXT"	/* the tradition UNIX text segment */
#define	SECT_TEXT	"__text"	/* the real text part of the text */
					/* section no headers, and no padding */
#define SECT_FVMLIB_INIT0 "__fvmlib_init0"	/* the fvmlib initialization */
						/*  section */
#define SECT_FVMLIB_INIT1 "__fvmlib_init1"	/* the section following the */
					        /*  fvmlib initialization */
						/*  section */

#define	SEG_DATA	"__DATA"	/* the tradition UNIX data segment */
#define	SECT_DATA	"__data"	/* the real initialized data section */
					/* no padding, no bss overlap */
#define	SECT_BSS	"__bss"		/* the real uninitialized data section*/
					/* no padding */
#define SECT_COMMON	"__common"	/* the section common symbols are */
					/* allocated in by the link editor */

#define	SEG_OBJC	"__OBJC"	/* objective-C runtime segment */
#define SECT_OBJC_SYMBOLS "__symbol_table"	/* symbol table */
#define SECT_OBJC_MODULES "__module_info"	/* module information */
#define SECT_OBJC_STRINGS "__selector_strs"	/* string table */
#define SECT_OBJC_REFS "__selector_refs"	/* string table */

#define	SEG_ICON	 "__ICON"	/* the icon segment */
#define	SECT_ICON_HEADER "__header"	/* the icon headers */
#define	SECT_ICON_TIFF   "__tiff"	/* the icons in tiff format */

#define	SEG_LINKEDIT	"__LINKEDIT"	/* the segment containing all structs */
					/* created and maintained by the link */
					/* editor.  Created with -seglinkedit */
					/* option to ld(1) for MH_EXECUTE and */
					/* FVMLIB file types only */

#define SEG_UNIXSTACK	"__UNIXSTACK"	/* the unix stack segment */

#define SEG_IMPORT	"__IMPORT"	/* the segment for the self (dyld) */
					/* modifing code stubs that has read, */
					/* write and execute permissions */


struct symtab_command {
	uint32_t	cmd;		/* LC_SYMTAB */
	uint32_t	cmdsize;	/* sizeof(struct symtab_command) */
	uint32_t	symoff;		/* symbol table offset */
	uint32_t	nsyms;		/* number of symbol table entries */
	uint32_t	stroff;		/* string table offset */
	uint32_t	strsize;	/* string table size in bytes */
};

/*
 * An indirect symbol table entry is simply a 32bit index into the symbol table
 * to the symbol that the pointer or stub is refering to.  Unless it is for a
 * non-lazy symbol pointer section for a defined symbol which strip(1) as
 * removed.  In which case it has the value INDIRECT_SYMBOL_LOCAL.  If the
 * symbol was also absolute INDIRECT_SYMBOL_ABS is or'ed with that.
 */
#define INDIRECT_SYMBOL_LOCAL	0x80000000
#define INDIRECT_SYMBOL_ABS	0x40000000

/*
 * Format of a symbol table entry of a Mach-O file for 32-bit architectures.
 * Modified from the BSD format.  The modifications from the original format
 * were changing n_other (an unused field) to n_sect and the addition of the
 * N_SECT type.  These modifications are required to support symbols in a larger
 * number of sections not just the three sections (text, data and bss) in a BSD
 * file.
 */
struct nlist {
	union {
#ifndef __LP64__
		char *n_name;	/* for use when in-core */
#endif
		uint32_t n_strx;	/* index into the string table */
	} n_un;
	uint8_t n_type;		/* type flag, see below */
	uint8_t n_sect;		/* section number or NO_SECT */
	int16_t n_desc;		/* see <mach-o/stab.h> */
	uint32_t n_value;	/* value of this symbol (or stab offset) */
};

/*
 * This is the symbol table entry structure for 64-bit architectures.
 */
struct nlist_64 {
    union {
        uint32_t  n_strx; /* index into the string table */
    } n_un;
    uint8_t n_type;        /* type flag, see below */
    uint8_t n_sect;        /* section number or NO_SECT */
    uint16_t n_desc;       /* see <mach-o/stab.h> */
    uint64_t n_value;      /* value of this symbol (or stab offset) */
};
#define	N_STAB	0xe0  /* if any of these bits set, a symbolic debugging entry */
#define	N_PEXT	0x10  /* private external symbol bit */
#define	N_TYPE	0x0e  /* mask for the type bits */
#define	N_EXT	0x01  /* external symbol bit, set for external symbols */


/*
 * Values for N_TYPE bits of the n_type field.
 */
#define	N_UNDF	0x0		/* undefined, n_sect == NO_SECT */
#define	N_ABS	0x2		/* absolute, n_sect == NO_SECT */
#define	N_SECT	0xe		/* defined in section number n_sect */
#define	N_PBUD	0xc		/* prebound undefined (defined in a dylib) */
#define N_INDR	0xa		/* indirect */

#define	NO_SECT		0	/* symbol is not in any section */
#define MAX_SECT	255	/* 1 thru 255 inclusive */

/* Reference type bits of the n_desc field of undefined symbols */
#define REFERENCE_TYPE				0x7
/* types of references */
#define REFERENCE_FLAG_UNDEFINED_NON_LAZY		0
#define REFERENCE_FLAG_UNDEFINED_LAZY			1
#define REFERENCE_FLAG_DEFINED				2
#define REFERENCE_FLAG_PRIVATE_DEFINED			3
#define REFERENCE_FLAG_PRIVATE_UNDEFINED_NON_LAZY	4
#define REFERENCE_FLAG_PRIVATE_UNDEFINED_LAZY		5




#endif
