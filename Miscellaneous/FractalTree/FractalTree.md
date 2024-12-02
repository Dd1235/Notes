# Some notes on making a fractal tree 
```

class Branch{
    Branch(start, end){
        this.start = start;
        this.end = end;
        this.finished = false;
    }
    void show(){
        drawLine(this.start.x, this.start.y, this.end.x, this.end.y);

    }
    void length(){
        return dist(this.start.x, this.start.y, this.end.x, this.end.y);
    }

    void jitter(){
        this.end.x += random(-1, 1);
        this.end.y += random(-1, 1);
    }

    pair<Branch,Branch>& createBranches(){
        if(length < 4){
            return null;
        }
        dir = subtract(this.end, this.start);
        dir.rotate(angle); // maybe 45
        dir.mult(0.67);
        newEnd = add(this.end, dir);
        right = newBranch(this.end, newEnd)
        dir.rotate(-2*angle);
        newEnd = add(this.end, dir);
        left = newBranch(this.end, newEnd)
    }
}

tree = []; // choose some appropriate size
leaves = [];
count = 0;
a = createVector(width/2, height);
b = createVector(width/2, height - 100);
root = new Branch(a, b);
tree[0] = root;
count++;

void mousePressed(){
    for(int i = tree.length - 1; i >= 0; i--){
        if(!tree[i].finished){
            [left, right] = tree[i].createBranches();
            if(left != null){
                tree.push(left);
            }
            if(right != null){
                tree.push(right);
            }
            tree[i].finished = true;
            count ++;
        }
    }
}


if(count == 5){
    for(var i = 0; i < tree.length; i++){
        if(!tree[i].finished){
            leaf = tree[i].end.copy();
            leaves.push(leaf);
        }
    }
}


void draw(){
    background(...);
    angle = slider.value();
    for(int i = 0; i < tree.length; i++){
        tree[i].show();
        tree[i].jitter();   
    }
    for(int i = 0; i < leavse.length(); i++){
        fill(255, 0, 100, 100);
        ellipse(leaves[i].x, leaves[i].y, 8, 8);
        leaves[i].y += random(0, 2);
    }

}

```