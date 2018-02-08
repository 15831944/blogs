/*********************************************************
    程序 12.7
        提炼简化的插入到一个有序的双链表
    参数
        指向当前节点的link字段指针的指针, 要插入的新节点的值
*********************************************************/
int doubly_linked_list_insert_v2 (register Node *root_pointer, int new_value)
{
    register Node *this;
    register Node *next;
    register Node *newnode;

    for (this = root_pointer; (next = this->fwd) != NULL; this = next)
    {
        if (next->value == value)
            return 0;
        if (next->value > value)
            break;
    }

    newnode = (Node *)malloc(sizeof(Node));
    if (newnode == NULL)
        return -1;
    newnode->value = new_value;

    newnode->fwd = next;
    this->fwd = newnode;

    // newnode->bwd = this != root_pointer ? this : NULL;
    // (next != NULL ? next : root_pointer)->bwd = newnode;

    if (this != root_pointer)
        newnode->bwd = this;
    else
        newnode->bwd = NULL;            // 插入起始处, 新节点的左侧为 NULL

    if (next != NULL)
        next->bwd = newnode;
    else
        root_pointer->bwd = newnode;    // 插入结尾处, 根指针的左侧为新节点

    return 1;
}

/*********************************************************
    程序 12.4
        简明的插入到一个有序的双链表
    参数
        指向当前节点的link字段指针的指针, 要插入的新节点的值
*********************************************************/
int doubly_linked_list_insert_v1 (register Node *root_pointer, int new_value)
{
    Node *this;
    Node *next;
    Node *newnode;

    for (this = root_pointer; (next = this->fwd) != NULL; this = next)
    {
        if (next->value == value)   //新值已经存在于链表中
            return 0;
        if (next->value > value)
            break;
    }

    newnode = (Node *)malloc(sizeof(Node));
    if (newnode == NULL)
        return -1;
    newnode->value = value;

    if (next != NULL)
    {
        /*中间位置*/
        if (this != root_pointer)
        {
            newnode->fwd = next;
            this->fwd = newnode;
            newnode->bwd = this;
            next->bwd = newnode;
        }
        /*起始位置*/
        else
        {
            newnode->fwd = next;
            root_pointer->fwd = newnode;
            newnode->bwd = NULL;
            next->bwd = newnode;
        }
    }
    else
    {
        /*结尾位置*/
        if (this != root_pointer)
        {
            newnode->fwd = NULL;
            this->fwd = newnode;
            newnode->bwd = this;
            root_pointer->bwd = newnode;
        }
        /*插入空链表*/
        else
        {
            newnode->fwd = NULL;
            root_pointer->fwd = newnode;
            newnode->bwd = NULL;
            root_pointer->bwd = newnode;
        }
    }
    return 1;
}

/*********************************************************
    程序 12.3
        插入到一个有序的单链表
    参数
        指向当前节点的link字段指针的指针, 要插入的新节点的值
*********************************************************/
int single_linked_list_insert_v3 (register Node **link_pointer, int new_value)
{
    register Node *current;
    register Node *new;

    while ((current = *link_pointer) != NULL && current->value < new_value)
        link_pointer = &current->link;

    new = (Node *)malloc(sizeof(Node));
    if (new == NULL)
        return FALSE;
    new->value = new_value;

    new->link = current;
    *link_pointer = new;
    return TRUE;
}

/********************************************
    程序 12.2
        插入到一个有序的单链表
    参数
        指向根节点的指针, 要插入的新节点的值
*********************************************/
int single_linked_list_insert_v2 (Node **root_pointer, int new_value)
{
    Node *current;
    Node *previous;
    Node *new;

    current = *root_pointer;        //对第一个参数执行间接访问
    previous = NULL;

    /*寻找插入位置*/
    while ( current != NULL && current->value < new_value)  //current指向
    {
        previous = current;         //始终保存指向前一个节点的指针
        current = current->link;    //同时也是调整部分
    }

    /*分配新节点*/
    new = (Node *) malloc(sizeof(Node));
    if (new == NULL)
        return FALSE;
    new->value = new_value;

    /*插入*/
    new->link = current;
    if (previous == NULL)
        *root_pointer = new;        //间接访问引用修改根指针
    else
        previous->link = new;
    return TRUE;
}

/********************************************
    程序 12.1
        插入到一个有序的单链表
    参数
        最后一个小于插入值的节点, 要插入的新节点的值
*********************************************/
int single_linked_list_insert_v1 (Node *current, int new_value)
{
    Node *previous;
    Node *new;

    /*寻找插入位置*/
    while (current->value < new_value)
    {
        previous = current;         //始终保存指向前一个节点的指针
        current = current->link;    //同时也是调整部分
    }

    /*分配新节点*/
    new = (Node *) malloc(sizeof(Node));
    if (new == NULL)
        return FALSE;
    new->value = new_value;

    /*插入*/
    new->link = current;
    previous->link = new;
    return TRUE;
}
