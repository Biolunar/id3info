#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static char* genres[] = {
	// Original 0 to 79
	"Blues", "Classic Rock", "Country", "Dance", "Disco", "Funk", "Grunge", "Hip-Hop", "Jazz", "Metal", "New Age",
	"Oldies", "Other", "Pop", "Rhythm and Blues", "Rap", "Reggae", "Rock", "Techno", "Industrial", "Alternative", "Ska", "Death Metal",
	"Pranks", "Soundtrack", "Euro-Techno", "Ambient", "Trip-Hop", "Vocal", "Jazz & Funk", "Fusion", "Trance", "Classical", "Instrumental",
	"Acid", "House", "Game", "Sound Clip", "Gospel", "Noise", "Alternative Rock", "Bass", "Soul", "Punk rock", "Space", "Meditative",
	"Instrumental Pop", "Instrumental Rock", "Ethnic", "Gothic", "Darkwave", "Techno-Industrial", "Electronic", "Pop-Folk", "Eurodance",
	"Dream", "Southern Rock", "Comedy", "Cult", "Gangsta", "Top 40", "Christian Rap", "Pop/Funk", "Jungle", "Native American", "Cabaret",
	"New Wave", "Psychedelic", "Rave", "Showtunes", "Trailer", "Lo-Fi", "Tribal", "Acid Punk", "Acid Jazz", "Polka", "Retro", "Musical",
	"Rock & Roll", "Hard Rock",
	// Winamp extensions 80 to 191
	"Folk", "Folk-Rock", "National Folk", "Swing", "Fast Fusion", "Bebop", "Latin", "Revival", "Celtic", "Bluegrass", "Avantgarde",
	"Gothic Rock", "Progressive Rock", "Psychedelic Rock", "Symphonic Rock", "Slow Rock", "Big Band", "Chorus", "Easy Listening", "Acoustic",
	"Humour", "Speech", "Chanson", "Opera", "Chamber Music", "Sonata", "Symphony", "Booty Bass", "Primus", "Porn groove", "Satire",
	"Slow Jam", "Club", "Tango", "Samba", "Folklore", "Ballad", "Power Ballad", "Rhythmic Soul", "Freestyle", "Duet", "Punk rock",
	"Drum Solo", "A capella", "Euro-House", "Dance Hall", "Goa", "Drum & Bass", "Club-House", "Hardcore Techno", "Terror", "Indie",
	"BritPop", "Afro-punk", "Polsk Punk", "Beat", "Christian Gangsta Rap", "Heavy Metal", "Black Metal", "Crossover", "Contemporary Christian",
	"Christian Rock", "Merengue", "Salsa", "Thrash Metal", "Anime", "Jpop", "Synthpop", "Abstract", "Art Rock", "Baroque", "Bhangra",
	"Big Beat", "Breakbeat", "Chillout", "Downtempo", "Dub", "EBM", "Eclectic", "Electro", "Electroclash", "Emo", "Experimental", "Garage",
	"Global", "IDM", "Illbient", "Industro-Goth", "Jam Band", "Krautrock", "Leftfield", "Lounge", "Math Rock", "New Romantic", "Nu-Breakz",
	"Post-Punk", "Post-Rock", "Psytrance", "Shoegaze", "Space Rock", "Trop Rock", "World Music", "Neoclassical", "Audiobook", "Audio Theatre",
	"Neue Deutsche Welle", "Podcast", "Indie Rock", "G-Funk", "Dubstep", "Garage Rock", "Psybient"
};


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	if (argc < 2)
	{
		printf("usage: id3info <filename>\n");
		printf("(c) 2014 Biolunar\n");
		return EXIT_SUCCESS;
	}

	FILE* file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Failed to open file.\n");
		return EXIT_FAILURE;
	}
	fseek(file, -128, SEEK_END);

	char tag[129];
	fread(tag, sizeof *tag, sizeof tag, file);
	fclose(file);

	if (strncmp(tag, "TAG", 3))
	{
		printf("No ID3v1 tag found.\n");
		return EXIT_SUCCESS;
	}

	printf("Title:   \"%.30s\"\n", tag+3);
	printf("Artist:  \"%.30s\"\n", tag+33);
	printf("Album:   \"%.30s\"\n", tag+63);
	printf("Year:    \"%.4s\"\n", tag+93);
	printf("Comment: \"%.30s\"\n", tag+97);
	if (!tag[125] && tag[126]) // v1.1
	{
		printf("Track:   \"%d\"\n", (int)*(tag+126));
	}
	if ((unsigned char)tag[127] > 191)
		tag[127] = 12; // set to 'Other'
	printf("Genre:   \"%s\"\n", genres[(size_t)(unsigned char)tag[127]]);

	return EXIT_SUCCESS;
}
