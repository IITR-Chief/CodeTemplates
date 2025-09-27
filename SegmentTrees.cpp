class SGTree{
    vector<int> SGTree;
    SGTree (int n) {
        SGTree.resize((4 * n) +1);
    }
    
    void build(int idx,int low ,int high,int arr[]){
        if(low==high){
            SGTree[idx]=arr[low];
            return;
        }
        
        int mid=(low+high)/2;
        build(2*idx+1, low, mid, arr);
        build(2*idx+2, mid+1, high, arr);
        
        SGTree[idx]=min(SGTree[2*idx+1],SGTree[2*idx+2]);
    }
    
    int query(int idx, int low, int high, int l, int r){
        // 3 cases
        // no overlap, complete overlap, partial overlap
        
        // noOverLap
        if(r<low || high<l) return INT_MAX;
        
        // CompleteOverlap
        if(low>=l && high<=r) return SGTree[idx];
        
        //partialOverlap:
        int mid=(low + high)/2;
        int left=query(2 * idx + 1, low, mid, l, r);
        int right=query(2 * idx + 2, mid+1, l, r);
        
        return min(left,right);
    }
    
    void update(int idx, int low, int high, int i, int val){
        if(low==high){
            SGTree[low]=val;
            return;
        }
        
        int mid=(low+high)/2;
        if(i<=mid) update(2*idx+1,low,mid,i,val);
        else update(2*idx+2,mid+1,high, i, val);
           
        SGTree[idx]=min(SGTree[2*idx+1],SGTree[2*idx+2]);
    }
};
