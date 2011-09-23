
// Código en C del Archivo en Bloques
// Luego va a ser pasado a C++

/*

#include "blockmgnt.h"
#include <sys/mman.h>


// Devuelve el tamaño del bloque
int getblocksize(struct filehandle *fh)
{   
    return fh->blocksize-1;
}

// Devuelve un bloque
int *getblock(struct filehandle *fh, int bh)
{

    int *block=fh->blocksize+bh*fh->blocksize;
    if(bh==0)
        return 0;
    if(bh>fh->maxblocknum)
        return 0;
    char filehead = (char)block[0];
    char *charlocation = (char*)block;
    charlocation++;
    if (filehead!='M')
        return (int*)charlocation;
    return 0;

};

// Nuevo block handle
int newblockhandle(struct filehandle *fh)
{
    int ret=retlastdeleted(fh);
    if(ret)
        return ret;
    return growfile(fh);
};


int retlastdeleted(struct filehandle *fh)
{

};


int delblockhandle(struct filehandle *fh, int blockhandle)
{

};

struct filehandle* openblockfile(char *path, int blocksize)
{
    int df=0;
    struct stat statbuf;
    struct filehandle *f=malloc(sizeof(struct filehandle));
    int *mem=0;

    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    if ((df = open (path, O_RDWR | O_CREAT, mode)) < 0)
    {
        perror("cannot open file");
        return 0;
    }

    if (fstat (df,&statbuf) < 0)
    {
        perror("cannot stat file");
        return 0;
    }

    if (statbuf.st_blocks==0)
    {
        lseek(df,blocksize-1,SEEK_END);
        write(df,"",sizeof(char));
        f.blocksize=blocksize+1;
        f.currmetadata=0;
        f.currpos=0;
        f.maxblocknum=0;
        if ((mem = mmap (0, blocksize+1, PROT_READ | PROT_WRITE, MAP_SHARED, df, 0))== (caddr_t) -1)
        {
            perror("mmap error for output\n");
            return 0;
        }
        serializehead(f);
    } else
    {
        if ((mem = mmap (0, stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, df, 0))== (caddr_t) -1)
        {
            perror("mmap error for output\n");
            return 0;
        }
        f->mem=mem;
        deserializehead(f);
    }
    f->fd=df;
    f->path=strdup(path);

    return f;
};

int serializehead(struct filehandle *fh)
{
   char *charblock=(char*)fh->mem;
   charblock[0]='H';
   charblock++;
   int *intblock=(int*)charblock;
   intblock[0]=fh->currmetadata;
   intblock[1]=fh->currpos;
   intblock[2]=fh->maxblocknum;
};

int deserializehead(struct filehandle *fh)
{
   char *charblock=(char*)fh->mem;
   charblock++;
   int *intblock=(int*)charblock;
   fh->currmetadata=intblock[0];
   fh->currpos=intblock[1];
   fh->maxblocknum=intblock[2];
};

int newmetadatahandle(struct filehandle *fh)
{

};

int delmetadatahandle(struct filehandle *fh)
{

};

char *readblock(struct filehandle *fh, int bh)
{
    char *ret=malloc(fh->blocksize-1);
    int mem=getblock(fh,bh);
    for(int i=0;i<fh->blocksize-1;i++)
        ret[i]=mem[i];
};

int writeblock(struct filehandle *fh, int bh, char *in)
{
    int mem=getblock(fh,bh);
    for(int i=0;i<fh->blocksize-1;i++)
        mem[i]=in[i];
}

int growfile(struct filehandle *fh)
{
    struct stat statbuf;
    int *mem;
    munmap(fh->mem);
    if (fstat (fh->fd,&statbuf) < 0)
    {
        perror("cannot stat file");
        return 0;
    }

    lseek(fh->fd,statbuf.st_size+fh->blocksize,SEEK_END);
    write(fh->fd,"",sizeof(char));
    if ((mem = mmap (0,statbuf.st_size+fh->blocksize, PROT_READ | PROT_WRITE, MAP_SHARED, fh->fd, 0))== (caddr_t) -1)
    {
       perror("mmap error for output\n");
       return 0;
    }
    fh->mem=mem;
    fh->maxblocknum+=1;
    serializehead(fh);
    return fh->maxblocknum;
}

int truncatefile(struct filehandle *fh)
{
    struct stat statbuf;
    int *mem;
    munmap(fh->mem);
    if (fstat (fh->fd,&statbuf) < 0)
    {
        perror("cannot stat file");
        return 0;
    }

    lseek(fh->fd,statbuf.st_size-fh->blocksize,SEEK_END);
    write(fh->fd,"",sizeof(char));
    if ((mem = mmap (0,statbuf.st_size-fh->blocksize, PROT_READ | PROT_WRITE, MAP_SHARED, fh->fd, 0))== (caddr_t) -1)
    {
       perror("mmap error for output\n");
       return 0;
    }
    fh->mem=mem;
    fh->maxblocknum-=1;
    serializehead(fh);
    return 1;
}


 *
 */
