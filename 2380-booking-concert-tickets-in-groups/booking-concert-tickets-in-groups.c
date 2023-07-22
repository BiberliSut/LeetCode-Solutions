typedef struct node { 
    int max;  
    long long sum;
    int range[2]; 
    struct node *left; 
    struct node *right;
} Node;   


typedef struct { 
    Node *root;
} BookMyShow; 

int p; /*num of rows*/ 
long long q; /*num of seats*/
 

void build(Node *root, int start, int end); 
int *max_query(Node *root, int k, int maxRow); 
int max_update(Node *root, int k, int row); 
void sum_aux(Node *root, int k, int maxRow); 
long long sum_query(Node *root, int maxRow);
Node *create_node(int start, int end); 


BookMyShow* bookMyShowCreate(int n, int m) {  
    int i;
    if(n<0 || m<0) 
        return NULL; 
    p = n; 
    q = m;
    BookMyShow *stadium = malloc(sizeof(BookMyShow)); 
    stadium->root = create_node(0,p); 
    build(stadium->root,0,p);
    
    return stadium;
}

int* bookMyShowGather(BookMyShow* obj, int k, int maxRow, int* retSize) { 
    if(obj == NULL) 
        return NULL; 
    Node *root = obj->root; 
    if(root->max < k) 
        return NULL;  
    printf("%d \n",root->max);
    printf("%d \n", root->sum);
    int *res = max_query(root, k, maxRow); 
    if(res){ 
        *retSize = 2; 
        max_update(root,k, res[0]);
    } 
    else 
        *retSize = 0; 
    return res;
}

bool bookMyShowScatter(BookMyShow* obj, int k, int maxRow) { 
    if(!obj) 
        return false; 
    Node *root = obj->root; 
    if(root->sum < k) 
        return false; 
    
    long long res = sum_query(root,maxRow); 
    bool ret = res >=k;
    if(ret)  
        sum_aux(root, k, maxRow) ; 
    
    return ret;
}

void bookMyShowFree(BookMyShow* obj) {
    
}  

int *max_query(Node *root, int k, int maxRow) {  
    if(!root || root->max < k || (root->range)[0] > maxRow) 
        return NULL; 
    else if(!root->left && !root->right) { 
        int *result = malloc(sizeof(int)*2); 
        (result)[0] = (root->range)[0]; 
        (result)[1] = (q - root->max);  
        return result; 
    } 
    
    int *l = max_query(root->left, k, maxRow); 
    if(l) 
        return l;
    else 
        return max_query(root->right, k, maxRow); 
}  

int max_update(Node *root, int k, int row) { /*try to recombine later*/
    if(!root) 
        return 0;  
    if((root->range)[0] > row || (root->range)[1] < row) 
        return root->max; 
    
    if(!root->left && !root->right) { 
        root->max -= k; 
        root->sum -= k; 
        return root->max;
    } 
    
    int l = max_update(root->left, k, row); 
    int r = max_update(root->right, k, row); 
    
    root->sum -= k; 
    root->max = l > r ? l : r;  
    
    return root->max;
} 

void sum_aux(Node *root, int k, int maxRow) { 
    if(!root) 
        return ; 
    if((root->range)[0] > maxRow) 
        return;  
    
    if(!root->left && !root->right) {
        root->max -= k; 
        root->sum -= k; 
        return ;
    }  
    
    root->sum -= k;
    if((root->right && (root->right->range)[0] > maxRow) ||  
           (root->left && root->left->sum >= k) ) 
        { 
            sum_aux(root->left, k, maxRow);
        } 
    else { 
        k -= root->left->sum; 
        sum_aux(root->left, root->left->sum, maxRow); 
        sum_aux(root->right, k, maxRow);
    }  
    
    root->max = root->left->max > root->right->max ?  
        root->left->max :  
        root->right->max; 
    return;
} 

long long sum_query(Node *root, int maxRow) { 
    if((root->range)[0] > maxRow) 
        return 0;  
    if((root->range)[1] <= maxRow) 
        return root->sum;  
    return sum_query(root->left, maxRow) + sum_query(root->right, maxRow);
}

void build(Node *root, int start, int end) { 
    if(root == NULL || start >= end) 
        return;  
    
    int split = (start+end)/2;
    root->left = create_node(start,split); 
    root->right = create_node(split+1,end);  
    
    build(root->left,start,split); 
    build(root->right,split+1,end); 

    return;
}

Node *create_node(int start, int end) { 
    Node *node = malloc(sizeof(Node));  
    node->max = q;
    node->sum = start == end ? q : q*((end-start)+1); 
    (node->range)[0] = start; 
    (node->range)[1] = end;  
    node->left = NULL; 
    node->right = NULL;
    return node;
}
