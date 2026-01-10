class Solution {
    public int[] solution(int e, int[] starts) {
        int[] answer = new int[starts.length];
        // 약수의 개수
        int[] cnt = new int[5000010];
        
        for (int i = 1; i <= 5000000; i++) {
        	for (int j = i; j <= 5000000; j+=i) {
        		cnt[j]++;
        	}
        }
        int ans[] = new int[e + 1];
        for (int i = 1; i <= e; i++) ans[i] = i;
        
        for (int i = e - 1; i >= 1; i--) {
        	if (cnt[i] < cnt[ans[i + 1]]) ans[i] = ans[i + 1];
        }
        
        
        for (int i = 0; i < answer.length; i++) {
        	answer[i] = ans[starts[i]];
        }
        return answer;
    }
}