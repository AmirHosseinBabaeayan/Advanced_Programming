using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

namespace Tura.Util
{
    public static class ActivationManager
    {
        public async static Task<bool> Activate(string key)
        {
            HttpRequestMessage h = new HttpRequestMessage();
            h.Content = new StringContent("Method=Activate&Key=" + key, Encoding.ASCII);
            //h.Headers.Add("Content-Type", "application/x-www-form-urlencoded");
            h.Method = HttpMethod.Post;
            h.RequestUri = new Uri("http://rmclassic.royalwebhosting.net/TuraActivation.php");
            HttpClient client = new HttpClient();

            h.Content.Headers.ContentType = new System.Net.Http.Headers.MediaTypeHeaderValue("application/x-www-form-urlencoded");
          string res =  await client.SendAsync(h).Result.Content.ReadAsStringAsync();
            if (res == "OK")
                return true;
            else
                return false;
        }

    }
}
