/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  School of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>

/* �꾩슂�� �ㅻ뜑�뚯씪 異붽� */
//원래 깨져 있었음



typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

//노드 자료형

/* �⑥닔 由ъ뒪�� */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);

//함수 설명은 전부 정의부에 있음


int main()
{
	char command;//명령
	int key;//값 저장 변수
	listNode* headnode=NULL; //헤드노드

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		//양식

		printf("Command = ");
		scanf(" %c", &command);//명령 받기

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode); //리스트 초기화
			break;
		case 'p': case 'P':
			printList(headnode);//리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);//값 받아서 적절한 위치에 넣기
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);//값 받아서 그 값의 노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);//값 받아서 리스트 마지막에 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode);//리스트 마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);//값 받아서 리스트 처음에 노드 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode);//리스트 첫 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);//리스트 역순으로
			break;
		case 'q': case 'Q':
			freeList(headnode);//리스트 삭제 및 종료
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");//부적절한 입력값 경고
			break;
		}

	}while(command != 'q' && command != 'Q');//종료 조건

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴*/
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){

	//앞과 뒤 노드 포인터
	listNode* front = h->rlink;
	listNode* back = h;

	while(front != h){
		back = front;//뒤 포인터를 앞으로 당기기
		front = front->rlink;//앞 포인터를 다음 노드로
		free(back);//뒤 포인터 할당 해제
	}

	free(h);//리스트 노드들 다 할당해제 후 헤드포인터까지 할당해제

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}
	
	//리스트가 초기화 필요시

	p = h->rlink;//노드 포인터를 리스트 첫 노드로

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}//리스트를 전부 돌면서 노드의 위치와 값 출력
	printf("  items = %d\n", i);//총 노드 수 출력


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);
	//헤드노드의 우링크와 좌링크 값 출력

	i = 0;//위치표시용 변수
	p = h->rlink; //포인터를 첫번째 노드로
	while(p != NULL && p != h) {//포인터가 NULL이 아니고 헤드노드도 아니면
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		//노드의 값, 위치, 좌링크, 노드의 주소, 우링크 출력
		p = p->rlink;//포인터를 다음 노드로
		i++;//위치 증가
	}

}



/**
 * list에 key에 대한 노드하나 추가
 */
int insertLast(listNode* h, int key) {

	if(h == NULL) {
		printf("Please initialize....\n");
		return 0;
	}//리스트 초기화 필요시

	listNode * front = h;//앞 포인터 = 헤드노드
	listNode * back = h->llink;//뒤 포인터 = 마지막 노드

	listNode* newNode = (listNode*)malloc(sizeof(listNode));//새 노드 할당

	front->llink = newNode;
	newNode->rlink = front;
	back->rlink = newNode;
	newNode->llink = back;
	//마지막노드와 헤드노드 사이에 새노드 연결
	newNode->key = key;//값

	return 1;
}


/**
 * list의 마지막 노드 학제
 */
int deleteLast(listNode* h) {

	if(h == NULL) {
		printf("Please initialize....\n");
		return 0;
	}//리스트 초기화 x시 출력

	listNode * back = h->llink->llink; //뒷 포인터 = 뒤에서 두번째 노드

	if(h->rlink == h) {printf("리스트 비어 있음"); return 0;} //리스트가 비어있으면 출력
	
	free(h->llink);//마지막 노드 할당해제

	h->llink = back;
	back->rlink = h;
	//뒤에서 마지막 노드와 헤드노드 연결
	

	return 1;
}


/**
 * list 처음에 key에 대한 노드 하나를 추가
 */
int insertFirst(listNode* h, int key) {

	if(h == NULL) {
		printf("Please initialize....\n");
		return 0;
	}//리스트 초기화 필요시

	
	listNode * front = h->rlink;//앞 포인터는 첫 노드
	listNode * back = h;//뒷 포인터는 헤드노드

	listNode* newNode = (listNode*)malloc(sizeof(listNode));//새노드 할당

	front->llink = newNode;
	newNode->rlink = front;
	back->rlink = newNode;
	newNode->llink = back;
	//새노드를 앞포인터와 뒷포인터 사이에 연결
	newNode->key = key;
	//값

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if(h == NULL) {
		printf("Please initialize....\n");
		return 0;
	}//초기화 필요시


	listNode * front = h->rlink->rlink;//앞 포인터는 앞에서 두번째 노드

	if(h->rlink == h) {printf("리스트 비어 있음"); return 0;}//리스트 비어있으면 출력

	free(h->rlink);//첫 노드 할당해제

	front->llink = h;
	h->rlink = front;
	//앞에서 두번째 노드와 헤드노드 연결


	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

	if(h == NULL) {
		printf("Please initialize....\n");
		return 0;
	}//초기화 필요시 출력

	listNode * cur = h;//현재 포인터는 헤드포인터
	listNode * temp;//임시용 포인터

	temp= h->rlink;
	h->rlink = h->llink;
	h->llink = temp;
	//헤드포인터 좌우연결 반대로

	cur = h->llink;//현재 포인터를 헤드포인터의 좌링크로

	while(cur != h){//다시 헤드노드로 돌아올때까지
	temp= cur->rlink;
	cur->rlink = cur->llink;
	cur->llink = temp;
	cur = cur->llink;
	//현재 노드의 좌우연결 반대로 하고 좌링크로 이동
	}

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰 값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h == NULL) {
		printf("Please initialize....\n");
		return 0;
	}//초기화 필요시 출력

	listNode * front = h->rlink;//앞 포인터는 첫 노드
	listNode * back = h;//뒷 포인터는 헤드 노드로

	listNode* newNode = (listNode*)malloc(sizeof(listNode));//새 노드 할당
	newNode->key = key;//값 넣기

	if(front == h){//헤드노드 밖에 없으면
		insertFirst(h, key);
		return 0;
	}

	back = back->rlink;
	front = front->rlink;
	//앞 뒤 포인터 한칸 앞으로

	while(front != h){//앞 포인터가 다시 헤드노드로 돌아올때 까지
		if(key < front->key && key >= back->key){//만약 입력값이 앞노드보다 작고 뒷노드보다 크거나 같으면
			back->rlink = newNode;
			newNode->llink = back;
			front->llink = newNode;
			newNode->rlink = front;
			//앞포인터와 뒷 포인터 사이에 새로운 노드 연결
			return 0;

		}
		back = back->rlink;
		front = front->rlink;
		//앞뒤 포인터 한칸 앞으로
	}	

	insertLast(h, key);//입력값이 가장 크면 새노드를 마지막 위치에 연결

	return 0;
}


/**
 * list�에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if(h == NULL) {
		printf("Please initialize....\n");
		return 0;
	}//초기화 필요시 출력

	listNode * front = h->rlink->rlink;//앞 포인터는 앞에서 두번째 노드
	listNode * back = h;//뒷 포인터는 헤드노드

	if(h->rlink == h) {printf("리스트 비어 있음"); return 0;}
	//리스트 비어있을 시 출력

	while(back->rlink != h){
		if(back->rlink->key == key){//앞과 뒤 포인터 사이에 값과 일치하는 노드 발견시
			free(back->rlink);
			front->llink = back;
			back->rlink = front;
			//할당 해제하고 앞과 뒤 노드 연결
			return 0;
		}
		front = front->rlink;
		back = back->rlink;
		//앞과 뒤 포인터 한칸 앞으로
	}

	printf("일치하는 노드 없음\n\n");//일치하는 노드 없으면 출력

	return 0;
}

