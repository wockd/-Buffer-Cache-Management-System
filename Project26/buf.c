#include <stdio.h>

#include <stdlib.h>

#include "buf.h"

#include "queue.h"

#include "Disk.c"



Buf* item;

struct Buf* tmp_item;



void BufInit(void)

{





    TAILQ_HEAD(bufList, Buf) ppBufList[HASH_ENTRY_NUM];

    TAILQ_HEAD(stateList, Buf) ppStateListHead[MAX_BUFLIST_NUM];



    TAILQ_HEAD(lruList, Buf) pLruListHead;





    for (int i = 0;i < HASH_ENTRY_NUM;i++)

        TAILQ_INIT(&ppBufList[i]);



    for (int i = 0;i < MAX_BUFLIST_NUM;i++)

        TAILQ_INIT(&ppStateListHead[i]);



    TAILQ_INIT(&pLruListHead);





    DevCreateDisk();

    DevOpenDisk();



}



void BufRead(int blkno, char* pData)

{

    int exist;

    exist = BufGet(blkno);

    if (exist == NULL) {

        item = malloc(sizeof(*item));

        if (item == NULL) {

            perror("malloc failed");

            exit(EXIT_FAILURE);

        }



        item->blkno = blkno;

        item->pMem = malloc(sizeof(32));

        DevReadBlock(blkno, item->pMem);



        TAILQ_INSERT_HEAD(&ppBufList[blkno % HASH_ENTRY_NUM], item, blist);

        TAILQ_INSERT_TAIL(&ppStateListHead[1], item, slist);

        item->state = 1;

        *pData = item->pMem;

    }
    else if (exist == blkno) {

        DevReadBlock(blkno, item->pMem);

        *pData = item->pMem;



    }





}





void BufWrite(int blkno, char* pData)

{

    int exist;

    exist = BufGet(blkno);

    if (exist == NULL) {

        item = malloc(sizeof(*item));

        if (item == NULL) {

            perror("malloc failed");

            exit(EXIT_FAILURE);

        }



        item->blkno = blkno;

        item->pMem = malloc(sizeof(BLOCK_SIZE));

        item->pMem = *pData;

        TAILQ_INSERT_HEAD(&ppBufList[blkno % HASH_ENTRY_NUM], item, blist);

        TAILQ_INSERT_TAIL(&ppStateListHead[0], item, slist);

        item->state = 0;





    }
    else if (exist == blkno) {

        if (item->state == 1) {//Å¬¸°

            item->pMem = *pData;

            TAILQ_REMOVE(&ppStateListHead[1], item, slist);

            TAILQ_INSERT_TAIL(&ppStateListHead[0], item, slist);

            item->state = 0;





        }
        else if (item->state == 0) {

            item->pMem = *pData;



        }

    }

}



void BufSync(void) {



}



Buf* BufGet(int blkno) {



    int h = blkno % HASH_ENTRY_NUM;

    TAILQ_FOREACH(item, &ppBufList[h], blist)

    {

        if (item->blkno == blkno)

            return  &ppBufList[h];

        else return NULL;

        // printf("%d  :    %d  \n", item->blkno, &ppBufList[h]);

    }



}



/*

 * GetBufInfoByListNum: Get all buffers in a list specified by listnum.

 *                      This function receives a memory pointer to "ppBufInfo" that can contain the buffers.

 */

void GetBufInfoByListNum(StateList listnum, Buf** ppBufInfo, int* pNumBuf)

{



}







/*

 * GetBufInfoInLruList: Get all buffers in a list specified at the LRU list.

 *                         This function receives a memory pointer to "ppBufInfo" that can contain the buffers.

 */

void GetBufInfoInLruList(Buf** ppBufInfo, int* pNumBuf)

{



}





/*

 * GetBufInfoInBufferList: Get all buffers in the buffer list.

 *                         This function receives a memory pointer to "ppBufInfo" that can contain the buffers.

 */

void GetBufInfoInBufferList(Buf** ppBufInfo, int* pNumBuf)

{

}

