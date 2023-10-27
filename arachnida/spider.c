#include <curl/curl.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	CURL *curl;

	curl = curl_easy_init();
	if (!curl)
	{
		fprintf(stderr, "curl_easy_init() failed\n");
		return (1);
	}

	curl_easy_setopt(curl, CURLOPT_URL, "");
}