typedef pair<double,double> pdd;
pdd operator-(pdd a,pdd b){return {a.F-b.F,a.S-b.S};}
pdd operator+(pdd a,pdd b){return {a.F+b.F,a.S+b.S};}
pdd operator*(pdd a,double x){return {a.F*x,a.S*x};}
double dot(pdd a,pdd b){return a.F*b.F+a.S*b.S;}
double cross(pdd a,pdd b){return a.F*b.S-a.S*b.F;}
struct bpmj{
	const double eps=1e-8;
	int n,m,id,l,r;
	pdd pt[55],q[1100];
	struct line{
		pdd x,y;
		double z;
		line(pdd _x,pdd _y):x(_x),y(_y){z=atan2(y.S,y.F);}
		line(){}
		bool operator<(const line &a)const{return z<a.z;}
	}a[550],dq[1005];
	pdd get_(line x,line y){
		pdd v=x.x-y.x;
		double d=cross(y.y,v)/cross(x.y,y.y);
		return x.x+x.y*d;
	}
	void solve(){
		dq[l=r=1]=a[1];
		for(int i=2;i<=id;++i){
			while(l<r&&cross(a[i].y,q[r-1]-a[i].x)<=eps) --r;
			while(l<r&&cross(a[i].y,q[l]-a[i].x)<=eps) ++l;
			dq[++r]=a[i];
			if(fabs(cross(dq[r].y,dq[r-1].y))<=eps){
				--r;
				if(cross(dq[r].y,a[i].x-dq[r].x)>eps) dq[r]=a[i];
			}
			if(l<r) q[r-1]=get_(dq[r-1],dq[r]);
		}
		while(l<r&&cross(dq[l].y,q[r-1]-dq[l].x)<=eps) --r;
		if(r-l<=1) return;
		q[r]=get_(dq[l],dq[r]);
	}
	void cal(){
		double ans=0;
		q[r+1]=q[l];
		for(int i=l;i<=r;++i) ans+=cross(q[i],q[i+1]);
		cout<<fixed<<setprecision(3)<<ans/2<<"\n";
	}
	void main_(){
		cin>>n;
		for(int x,y,i=0;i<n;++i){
			cin>>m;
			for(int i=0;i<m;++i) cin>>pt[i].F>>pt[i].S;
			pt[m]=pt[0];
			for(int i=0;i<m;++i) a[++id]=line(pt[i],pt[i+1]-pt[i]);
		}
		sort(a+1,a+1+id);
		solve();
		cal();
	}
}valderyaya;
