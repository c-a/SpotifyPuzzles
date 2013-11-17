
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.PriorityQueue;
import java.util.StringTokenizer;
import java.util.Comparator;

public class Main {

	private static class Song{
		String name;
		long f;
		int index;
		
		public Song(String name, long f, int index) {
			this.name = name;
			this.f = f;
			this.index = index;
		}
	}
	public Main(BufferedReader in) throws Exception {
		StringTokenizer st = new StringTokenizer(in.readLine());
		
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		
		PriorityQueue<Song> PQ = new PriorityQueue<Song>(m, new Comparator<Song>() {

			@Override
			public int compare(Song o1, Song o2) {
				if (o1.f == o2.f)
					return o2.index - o1.index;
			else
				return (int)Math.signum(o1.f - o2.f);
			}
			
		});
		for (int i = 0; i < n; i++) {
			st = new StringTokenizer(in.readLine());
			
			long f = Long.parseLong(st.nextToken()) * (i+1);
			String name = st.nextToken();
			
			PQ.add(new Song(name, f, i));
			if (PQ.size() > m)
				PQ.poll();
		}
		
		Song[] songs = new Song[m];
		int s = 0;
		while (!PQ.isEmpty())
			songs[s++] = PQ.poll();
		
		for (int i = s-1; i >= 0; i--) {
			System.out.println(songs[i].name);
		}
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader is = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(is);
		
		new Main(in);
	}

}
