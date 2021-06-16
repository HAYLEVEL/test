using NUnit.Framework;
using System;
using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;

namespace NUnitTestProject4
{
    class Chrome
    {
        IWebDriver driver;
        string Url = "http://Google.com";


        [SetUp]
        public void startBrowser()
        {
            driver = new ChromeDriver();
            driver.Manage().Window.Maximize();
            System.Threading.Thread.Sleep(timeout: TimeSpan.FromSeconds(3));
            driver.Url = Url;
        }
        [Test]
        public void TestSearchRozklad()
        {
            IWebElement element;
            // Google search
            element = driver.FindElement(By.XPath("/html/body/div[1]/div[3]/form/div[1]/div[1]/div[1]/div/div[2]/input"));
            element.SendKeys("Кпи розклад");
            element.SendKeys(Keys.Enter);
            element = driver.FindElement(By.ClassName("iUh30"));
            element.Click();
            //Find KP-91 Schedule
            element = driver.FindElement(By.XPath("//*[@id=\"ctl00_MainContent_ctl00_txtboxGroup\"]"));
            element.SendKeys("Кп-91");
            element = driver.FindElement(By.XPath("//*[@id=\"ctl00_MainContent_ctl00_btnShowSchedule\"]"));
            element.Click();
            element = driver.FindElement(By.XPath("//*[@id=\"ctl00_MainContent_FirstScheduleTable\"]/tbody/tr[1]/td[4]"));
            if (element.Text.Contains("Середа"))
            {
                element = driver.FindElement(By.XPath("//*[@id=\"ctl00_MainContent_FirstScheduleTable\"]/tbody/tr[2]/td[4]/span/a"));
                if (element.Text.Contains("Якість та тестування програмного забезпечення"))
                {
                    System.Threading.Thread.Sleep(5000);
                    Console.Beep();
                }

            }

        }
        [Test]
        public void TestEpicenterSchedule()
        {
            IWebElement element;
            // Google search
            element = driver.FindElement(By.XPath("/html/body/div[1]/div[3]/form/div[1]/div[1]/div[1]/div/div[2]/input"));
            element.SendKeys("Epicenter");
            element.SendKeys(Keys.Enter);
            element = driver.FindElement(By.ClassName("iUh30"));
            element.Click();
            //Click on information 
            element = driver.FindElement(By.XPath("/html/body/div[2]/header/div/div[8]/div/div[2]"));
            element.Click();
            //CLick on contacts
            element = driver.FindElement(By.XPath("/html/body/div[2]/header/div/div[8]/div/div[2]/div[2]/a[2]"));
            element.Click();
            element = driver.FindElement(By.XPath("/html/body/main/div[2]/div/section/h3"));
            if (element.Text.Contains("з 07:30 до 22:30"))
            {
                System.Threading.Thread.Sleep(5000);
                Console.Beep();
            }
            Console.Beep();

        }



        [Test]
        public void TestAbaddonPhaseBoots()
        {
            IWebElement element;
            // Google search
            element = driver.FindElement(By.XPath("/html/body/div[1]/div[3]/form/div[1]/div[1]/div[1]/div/div[2]/input"));
            element.SendKeys("dotabuff");
            element.SendKeys(Keys.Enter);
            element = driver.FindElement(By.ClassName("iUh30"));
            element.Click();
            //Click on Heroes
            element = driver.FindElement(By.XPath("/html/body/div[1]/div[2]/div/nav/ul/li[4]/a"));
            element.Click();
            //Click on Abaddon
            element = driver.FindElement(By.XPath("/ html / body / div[1] / div[7] / div[3] / div[4] / section[2] / footer / div / a[1] / div / div[2]"));
            element.Click();
            //Check that Phase boots is top 1 item
            element = driver.FindElement(By.XPath("/html/body/div[1]/div[7]/div[3]/div[4]/div[1]/div[1]/section[4]/article/table/tbody/tr[1]/td[2]"));
            if (element.Text.Contains("Phase Boots")) ;
            {
                System.Threading.Thread.Sleep(5000);
                Console.Beep();
            }

        }
        [TearDown]
        public void closeBrowser()
        {
            driver.Close();
        }
    }
}
